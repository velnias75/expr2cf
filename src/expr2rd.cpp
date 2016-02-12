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
#include <unistd.h>

#if HAVE_STXXL
#include <stxxl/vector>
#endif

#include <rational/gmp_rational.h>

typedef Commons::Math::Rational<Commons::Math::gmp_rational::integer_type,
        Commons::Math::gmp_rational::gcd, Commons::Math::NO_OPERATOR_CHECK> gmp_pool_rational;

typedef Commons::Math::Rational<Commons::Math::gmp_rational::integer_type, Commons::Math::GCD_null,
        Commons::Math::NO_OPERATOR_CHECK> gmp_nogcd_rational;

int main ( int argc, const char *argv[] ) {

#if HAVE_STXXL
    const char *TMPDIR = std::getenv ( "TMPDIR" );
    std::ostringstream sxxl_disk;

    sxxl_disk << ( TMPDIR ? TMPDIR : "/tmp" ) << "/expr2rd_stxxl." << getpid();

    stxxl::config::get_instance()->add_disk ( stxxl::disk_config ( sxxl_disk.str(), 0u,
            "syscall nodirect autogrow delete_on_exit" ) );
#endif

    mpf_set_default_prec ( 65536 );

#ifdef HAVE_MPREAL_H
    mpfr_set_default_prec ( std::min<mpfr_prec_t> ( 65536, MPFR_PREC_MAX ) );
#endif

    try {

        gmp_nogcd_rational r;

        std::cin >> std::noskipws >> r;

#if !defined(HAVE_STXXL)
        std::vector<gmp_pool_rational::rf_info::digit_type> pre, rep;
#else
        stxxl::VECTOR_GENERATOR<gmp_pool_rational::rf_info::digit_type>::result pre, rep;
#endif

        gmp_pool_rational::rf_info i;

        const gmp_pool_rational::integer_type &w ( gmp_pool_rational ( r.numerator(),
                r.denominator() ). decompose ( i, pre, rep, true ) );

        const std::string v ( argc > 1 ? argv[1] : "" );

        if ( v == "-v" || v == "--verbose" ) {

            if ( !pre.empty() ) std::cerr << ( !rep.empty() ? "Pre    : " : "Tail: " )
                                              << pre.size() << std::endl;

            if ( !rep.empty() ) std::cerr << "Reptend: " << rep.size() << std::endl;
        }

        std::cout << w;

        if ( ! ( pre.empty() && rep.empty() ) ) std::cout << ".";

        if ( !pre.empty() ) {

            std::copy ( pre.begin(), pre.end(),
                        std::ostream_iterator<gmp_pool_rational::integer_type> ( std::cout ) );
        }

        if ( !rep.empty() ) {

            std::cout << '(';

            std::copy ( rep.begin(), rep.end(),
                        std::ostream_iterator<gmp_pool_rational::integer_type> ( std::cout ) );

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
