/*
 * Copyright 2015-2016 by Heiko Schäfer <heiko@rangun.de>
 *
 * This file is part of expr2cf.
 *
 * expr2cf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * expr2cf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with expr2cf.  If not, see <http://www.gnu.org/licenses/>.
 */

#if defined(HAVE_CONFIG_H) || defined(IN_IDE_PARSER)
#include "config.h"
#endif

#include <iostream>
#include <iterator>

#if defined(BOOST_POOL_ALLOC)
#include <boost/pool/pool_alloc.hpp>
#elif (defined(__GNUG__) || defined(__clang__))
#include <ext/pool_allocator.h>
#endif

#include <rational/gmp_rational.h>

typedef Commons::Math::Rational<Commons::Math::gmp_rational::integer_type, Commons::Math::GCD_null,
        Commons::Math::NO_OPERATOR_CHECK> gmp_nogcd_rational;

#if defined(BOOST_POOL_ALLOC)
struct _boost_pool_alloc_cleanup {
	~_boost_pool_alloc_cleanup() {
		boost::singleton_pool<boost::pool_allocator_tag,
			sizeof(Commons::Math::gmp_rational::rf_info::digit_type)>::release_memory();
	}
};
#endif

int main ( int argc, const char *argv[] ) {

    mpf_set_default_prec ( 65536 );

#ifdef HAVE_MPREAL_H
    mpfr_set_default_prec ( std::min<mpfr_prec_t> ( 65536, MPFR_PREC_MAX ) );
#endif

    try {

        gmp_nogcd_rational r;

        std::cin >> std::noskipws >> r;

        Commons::Math::gmp_rational::rf_info i;

#if defined(BOOST_POOL_ALLOC)
		const _boost_pool_alloc_cleanup bpac;

		std::vector<Commons::Math::gmp_rational::rf_info::digit_type,
            boost::pool_allocator<Commons::Math::gmp_rational::rf_info::digit_type> > pre, rep;
#elif (defined(__GNUG__) || defined(__clang__))
        std::vector<Commons::Math::gmp_rational::rf_info::digit_type,
            __gnu_cxx::__pool_alloc<Commons::Math::gmp_rational::rf_info::digit_type> > pre, rep;
#else
        std::vector<Commons::Math::gmp_rational::rf_info::digit_type> pre, rep;
#endif

        const Commons::Math::gmp_rational::integer_type &
        w ( Commons::Math::gmp_rational ( r.numerator(), r.denominator() ).
            decompose ( i, pre, rep, true ) );

        const std::string v ( argc > 1 ? argv[1] : "" );

        if ( v == "-v" || v == "--verbose" ) {

            if ( !pre.empty() ) std::cerr << ( !rep.empty() ? "Pre    : " : "Tail: " )
                                              << pre.size() << std::endl;

            if ( !rep.empty() ) std::cerr << "Reptend: " << rep.size() << std::endl;
        }

        std::cout << ( ( ( r.numerator() < Commons::Math::gmp_rational::zero_ ) &&
                         w >= Commons::Math::gmp_rational::zero_ ) ? "-" : "" ) << w;

        if ( ! ( pre.empty() && rep.empty() ) ) std::cout << ".";

        if ( !pre.empty() ) {

            std::copy ( pre.begin(), pre.end(),
                        std::ostream_iterator<Commons::Math::gmp_rational::integer_type>
                        ( std::cout ) );
        }

        if ( !rep.empty() ) {

            std::cout << '(';

            std::copy ( rep.begin(), rep.end(),
                        std::ostream_iterator<Commons::Math::gmp_rational::integer_type>
                        ( std::cout ) );

            std::cout << ')';
        }

        std::cout << std::endl;

    } catch ( const std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
