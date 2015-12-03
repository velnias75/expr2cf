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

#include <rational/gmp_rational.h>

int main ( int argc, const char *argv[] ) {

    if ( argc == 1 ) {
        std::cout << "Usage: repeating digit seq " \
                  "[leading zeros] [initial digit seq] [leading zeros before initial seq]"
                  << std::endl;

        return EXIT_SUCCESS;
    }

    mpf_set_default_prec ( 256 );

#ifdef HAVE_MPREAL_H
    mpfr_set_default_prec ( std::min<mpfr_prec_t> ( 256, MPFR_PREC_MAX ) );
#endif

    try {

        const Commons::Math::gmp_rational::integer_type x ( argc > 1 ? argv[1] : "0" );
        const Commons::Math::gmp_rational::integer_type pre ( argc > 3 ? argv[3] : "0" );
        const std::size_t lz ( argc > 2 ? static_cast<std::size_t> ( std::atol ( argv[2] ) ) :
                               0u );
        const std::size_t plz ( argc > 4 ? static_cast<std::size_t> ( std::atol ( argv[4] ) ) :
                                0u );

        std::cout << Commons::Math::gmp_rational ( Commons::Math::gmp_rational::rf_info ( x, lz,
                  pre, plz ) ) << std::endl;

    } catch ( const std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
