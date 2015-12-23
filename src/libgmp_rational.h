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

#ifndef LIBGMP_RATIONAL_H
#define LIBGMP_RATIONAL_H

#include <rational/gmp_rational.h>

namespace Commons {

namespace Math {

extern template class __attribute__((visibility("default")))
	Rational<mpz_class, GCD_gmp, NO_OPERATOR_CHECK>;

extern template class __attribute__((visibility("default")))
    Rational<mpz_class, GCD_null, NO_OPERATOR_CHECK>;

typedef Rational<gmp_rational::integer_type, GCD_null, NO_OPERATOR_CHECK> gmp_nogcd_rational;

}

}

#endif /* LIBGMP_RATIONAL_H */
