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

#include "libgmp_rational.h"

int main ( int argc, const char * argv[] ) {

    mpf_set_default_prec ( 65536 );

#ifdef HAVE_MPREAL_H
    mpfr_set_default_prec ( std::min<mpfr_prec_t> ( 65536, MPFR_PREC_MAX ) );
#endif

    try {

        Commons::Math::gmp_rational r;
        const Commons::Math::gmp_rational::integer_type i ( argc > 1 && * ( argv[1] ) ? argv[1] :
                "1" );

        std::cin >> std::noskipws >> r;

        typedef Commons::Math::Rational<Commons::Math::gmp_rational::integer_type,
                Commons::Math::GCD_null, Commons::Math::NO_OPERATOR_CHECK> gmp_nogcd_rational;

        const gmp_nogcd_rational &nr ( gmp_nogcd_rational ( r.numerator(),
                                       r.denominator() ).pow ( i ) );

        std::cout << Commons::Math::gmp_rational ( nr.numerator(), nr.denominator() ) << std::endl;

    } catch ( const std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
