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
#include <cstdint>

#include <rational/gmp_rational.h>

typedef Commons::Math::Rational<Commons::Math::gmp_rational::integer_type,
        Commons::Math::gmp_rational::gcd, Commons::Math::NO_OPERATOR_CHECK> gmp_gcd_rational;

typedef Commons::Math::Rational<Commons::Math::gmp_rational::integer_type, Commons::Math::GCD_null,
        Commons::Math::NO_OPERATOR_CHECK> gmp_nogcd_rational;

struct digit_stdout_container {

    typedef gmp_gcd_rational::rf_info::digit_type value_type;
    typedef uint64_t size_type;

    typedef struct _iterator : public std::iterator<std::input_iterator_tag, value_type> {

        _iterator () : pos_ ( 0u ) {}

        _iterator operator++ ( int ) {
            _iterator tmp ( *this );
            ++pos_;
            return tmp;
        }

        _iterator &operator++ () {
            ++pos_;
            return *this;
        }

        reference operator*() const {
            return tv_;
        }

        bool operator== ( const _iterator &o ) const {
            return pos_ == o.pos_;
        }

        bool operator!= ( const _iterator &o ) const {
            return pos_ != o.pos_;
        }

    private:
        size_type pos_;
        static value_type tv_;
    } iterator;

    explicit digit_stdout_container ( bool rep ) : size_ ( 0u ), rep_ ( rep ), first_ ( true ) {}

    iterator begin() {
        return iterator ();
    }

    iterator end() {
        return iterator ();
    }

    iterator insert ( iterator i, value_type &&v ) {

        gmp_printf ( "%s%Zd", ! ( rep_ && first_ ) ? "" : "(", v.get_mpz_t() );

        first_ = false;
        ++size_;

        return ++i;
    }

    void clear() {
        size_ = 0u;
    }

    size_type size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0u;
    }

private:
    size_type size_;
    const bool rep_;
    bool first_;
};

digit_stdout_container::_iterator::value_type digit_stdout_container::_iterator::tv_;

int main ( int argc, const char *argv[] ) {

    mpf_set_default_prec ( 65536 );

#ifdef HAVE_MPREAL_H
    mpfr_set_default_prec ( std::min<mpfr_prec_t> ( 65536, MPFR_PREC_MAX ) );
#endif

    try {

        gmp_nogcd_rational r;

        std::cin >> std::noskipws >> r;

        digit_stdout_container pre ( false ), rep ( true );

        gmp_gcd_rational::rf_info i;
        const auto &m ( r.mod() );

        std::cout << ( ! ( m.first >= gmp_nogcd_rational::rf_info::digit_type() &&
                           m.second.numerator() < gmp_nogcd_rational::zero_ ) ? "" : "-" )
                  << m.first << ( m.second == gmp_nogcd_rational() ||
                                  gmp_nogcd_rational::isInteger ( m ) ? "" : "." );

        gmp_gcd_rational ( r.numerator(), r.denominator() ).decompose ( i, pre, rep, true );

        if ( !rep.empty() ) std::cout << ')';

        std::cout << std::endl;

        const std::string v ( argc > 1 ? argv[1] : "" );

        if ( v == "-v" || v == "--verbose" ) {

            if ( !pre.empty() ) std::cerr << ( !rep.empty() ? "Pre    : " : "Tail: " )
                                              << pre.size() << std::endl;

            if ( !rep.empty() ) std::cerr << "Reptend: " << rep.size() << std::endl;
        }

    } catch ( const std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
