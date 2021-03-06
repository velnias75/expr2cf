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

#include <rational/gmp_rational.h>

struct cf_reader : std::ctype<char> {

    explicit cf_reader ( std::size_t refs = 0 ) : std::ctype<char> ( get_table(), false, refs ) {}

    static std::ctype_base::mask const *get_table() {

        static std::vector<std::ctype_base::mask> rc ( table_size, std::ctype_base::mask() );

        rc[',']  = std::ctype_base::space;
        rc[' ']  = std::ctype_base::space;
        rc['[']  = std::ctype_base::space;
        rc[']']  = std::ctype_base::space;
        rc['\n'] = std::ctype_base::space;

        return &rc[0];
    }
};

int main ( int argc, const char *argv[] ) {

    mpf_set_default_prec ( 65536 );

    try {

        std::cin.imbue ( std::locale ( std::locale(), new cf_reader ) );

        const std::string mixed ( argc > 1 ? argv[1] : "" );

        const Commons::Math::gmp_rational &r ( Commons::Math::cf (
                std::istream_iterator<Commons::Math::gmp_rational::integer_type> ( std::cin ),
                std::istream_iterator<Commons::Math::gmp_rational::integer_type>() ) );

        if ( mixed == "-m" || mixed == "--mixed" ) {

            std::string ms ( r.str ( true ) );
            std::cout << ms.replace ( ms.find_first_of ( ' ' ), 1u, "+" ) << std::endl;

        } else {
            std::cout << r << std::endl;
        }

    } catch ( const std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
