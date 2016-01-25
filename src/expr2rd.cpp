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

#include <iostream>
#include <iterator>
#include <iomanip>

#include <rational/gmp_rational.h>

typedef Commons::Math::Rational<Commons::Math::gmp_rational::integer_type, Commons::Math::GCD_null,
        Commons::Math::NO_OPERATOR_CHECK> gmp_nogcd_rational;

int main ( int argc, const char *argv[] ) {

    mpf_set_default_prec ( 65536 );

#ifdef HAVE_MPREAL_H
    mpfr_set_default_prec ( std::min<mpfr_prec_t> ( 65536, MPFR_PREC_MAX ) );
#endif

    try {

        gmp_nogcd_rational r;

        std::cin >> std::noskipws >> r;

        Commons::Math::gmp_rational::rf_info i;
        std::vector<Commons::Math::gmp_rational::rf_info::digit_type> pre, rep;

        const Commons::Math::gmp_rational::integer_type &
        w ( Commons::Math::gmp_rational ( r.numerator(), r.denominator() ).
            decompose ( i, pre, rep ) );

        if(argc > 1 && (std::string(argv[1]) == "-v" || std::string(argv[1]) == "--verbose")) {
			if(!pre.empty()) std::cerr << (!rep.empty() ? "Pre    : " : "Tail: ")
				<< pre.size() << std::endl;
			if(!rep.empty()) std::cerr << "Reptend: " << rep.size() << std::endl;
		}

        std::cout << ( ( ( r.numerator() < Commons::Math::gmp_rational::zero_ )
                         && w >= Commons::Math::gmp_rational::zero_ ) ? "-" : "" ) << w;

        if ( ! ( pre.empty() && rep.empty() ) ) std::cout << ".";

        if ( !pre.empty() ) {
            std::cout << std::setfill ( '0' )
                      << std::setw ( static_cast<int> ( pre.size() ) ) << i.pre;
        }

        if ( !rep.empty() ) {
            std::cout << '(' << std::setfill ( '0' )
                      << std::setw ( static_cast<int> ( rep.size() ) ) << i.reptend << ')';
        }

        std::cout << std::endl;

    } catch ( const std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
