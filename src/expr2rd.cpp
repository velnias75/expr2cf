/*
 * Copyright 2015 by Heiko Schäfer <heiko@rangun.de>
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

#include "libgmp_rational.h"

int main ( int, const char *[] ) {

    mpf_set_default_prec ( 65536 );

#ifdef HAVE_MPREAL_H
    mpfr_set_default_prec ( std::min<mpfr_prec_t> ( 65536, MPFR_PREC_MAX ) );
#endif

    try {

        Commons::Math::gmp_nogcd_rational r;

        std::cin >> std::noskipws >> r;

        Commons::Math::gmp_rational::rf_info i;

        const Commons::Math::gmp_rational::integer_type &
        w ( Commons::Math::gmp_rational ( r.numerator(), r.denominator() ).decompose ( i ) );

        std::cout << ( ( ( r.numerator() < Commons::Math::gmp_rational::zero_ )
                         && w >= Commons::Math::gmp_rational::zero_ ) ? "-" : "" ) << w;

        if ( ! ( i.pre_digits.empty() && i.reptend_digits.empty() ) ) std::cout << ".";

        if ( !i.pre_digits.empty() ) {
            std::cout << std::setfill ( '0' )
                      << std::setw ( static_cast<int> ( i.pre_digits.size() ) )
                      << i.pre;
        }

        if ( !i.reptend_digits.empty() ) {
            std::cout << '(' << std::setfill ( '0' )
                      << std::setw ( static_cast<int> ( i.reptend_digits.size() ) )
                      << i.reptend << ')';
        }

        std::cout << std::endl;

    } catch ( const std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
