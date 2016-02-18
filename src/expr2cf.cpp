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

template<class T, class charT = char, class traits = std::char_traits<charT> >
class infix_ostream_iterator :
    public std::iterator<std::output_iterator_tag, void, void, void, void> {

    std::basic_ostream<charT, traits> *os;
    charT const* delimiter;
    bool first_elem;

public:
    typedef charT char_type;
    typedef traits traits_type;
    typedef std::basic_ostream<charT, traits> ostream_type;

    explicit infix_ostream_iterator ( ostream_type& s ) : os ( &s ), delimiter ( 0L ),
        first_elem ( true ) {}

    infix_ostream_iterator ( ostream_type& s, charT const *d ) : os ( &s ), delimiter ( d ),
        first_elem ( true ) {}

    infix_ostream_iterator<T, charT, traits> &operator= ( T const &item ) {

        if ( !first_elem && delimiter != 0 ) *os << delimiter;

        *os << item;

        first_elem = false;

        return *this;
    }

    infix_ostream_iterator<T, charT, traits> &operator*() {
        return *this;
    }

    infix_ostream_iterator<T, charT, traits> &operator++() {
        return *this;
    }

#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic push
    infix_ostream_iterator<T, charT, traits> &operator++ ( int ) {
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

        const Commons::Math::gmp_rational t ( r.numerator(), r.denominator() );
        const gmp_nogcd_rational s ( t.numerator(), t.denominator() );

        Commons::Math::seq ( s,
                             infix_ostream_iterator<gmp_nogcd_rational::integer_type> ( std::cout,
                                     ", " ) );

        std::cout << "]" << std::endl;

    } catch ( const std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
