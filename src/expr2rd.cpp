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

#include <rational/gmp_rational.h>

static const char *EMPTY = "{-}";
static const char *COMMA = ", ";

int main(int, const char *[]) {

	mpf_set_default_prec(65536);

#ifdef HAVE_MPREAL_H
	mpfr_set_default_prec(std::min<mpfr_prec_t>(65536, MPFR_PREC_MAX));
#endif

	try {

		Commons::Math::gmp_rational r;

		std::cin >> std::noskipws >> r;

		Commons::Math::gmp_rational::rf_info i;

		std::cout << "[ " << r.decompose(i) << COMMA;

		if(!i.pre_digits.empty()) {

			std::copy(i.pre_digits.begin(), i.pre_digits.end(),
				std::ostream_iterator<Commons::Math::gmp_rational::integer_type>(std::cout));

		} else {
			std::cout << EMPTY;
		}

		std::cout << COMMA;

		if(!i.reptent_digits.empty()) {

			std::copy(i.reptent_digits.begin(), i.reptent_digits.end(),
				std::ostream_iterator<Commons::Math::gmp_rational::integer_type>(std::cout));

		} else {
			std::cout << EMPTY;
		}

		std::cout << " ]" << std::endl;

	} catch(const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}