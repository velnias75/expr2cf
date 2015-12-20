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

#include "libgmp_rational.h"

template class Commons::Math::Rational<mpz_class, Commons::Math::GCD_gmp,
         Commons::Math::NO_OPERATOR_CHECK>;

#if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) < 40800

template bool Commons::Math::Rational<mpz_class, Commons::Math::GCD_gmp,
         Commons::Math::NO_OPERATOR_CHECK>::isLeftAssoc ( char );

template unsigned char Commons::Math::Rational<mpz_class, Commons::Math::GCD_gmp,
         Commons::Math::NO_OPERATOR_CHECK>::getPrec ( char );

template bool Commons::Math::Rational<mpz_class, Commons::Math::GCD_gmp,
         Commons::Math::NO_OPERATOR_CHECK>::operator> ( Commons::Math::gmp_rational const& ) const;

template bool Commons::Math::Rational<mpz_class, Commons::Math::GCD_gmp,
         Commons::Math::NO_OPERATOR_CHECK>::operator< ( Commons::Math::gmp_rational const& ) const;

#endif

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
