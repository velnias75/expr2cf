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

#include <rational/gmp_rational.h>

typedef Commons::Math::Rational<Commons::Math::gmp_rational::integer_type, Commons::Math::GCD_null,
        Commons::Math::NO_OPERATOR_CHECK> gmp_nogcd_rational;

class infix_gmp_printf_iterator :
    public std::iterator<std::output_iterator_tag, void, void, void, void> {

    bool first_elem;

public:
    infix_gmp_printf_iterator () : first_elem ( true ) {}

    infix_gmp_printf_iterator &operator= ( gmp_nogcd_rational::integer_type const &item ) {

        if ( !first_elem ) std::printf ( "%s", ", " );

        gmp_printf ( "%Zd", item.get_mpz_t() );

        first_elem = false;

        return *this;
    }

    infix_gmp_printf_iterator &operator*() {
        return *this;
    }

    infix_gmp_printf_iterator &operator++() {
        return *this;
    }

#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic push
    infix_gmp_printf_iterator &operator++ ( int ) {
        return *this;
    }
#pragma GCC diagnostic pop
};

int main ( int, const char *[] ) {

    mpf_set_default_prec ( 65536 );

#ifdef HAVE_MPREAL_H
    mpfr_set_default_prec ( std::min<mpfr_prec_t> ( 65536, MPFR_PREC_MAX ) );
#endif

    try {

        gmp_nogcd_rational r;

        std::cin >> std::noskipws >> r;

        std::cout << "[";

        Commons::Math::seq ( r, infix_gmp_printf_iterator() );

        std::cout << "]" << std::endl;

    } catch ( const std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
