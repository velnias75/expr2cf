/*
 * Copyright 2015 by Heiko Schäfer <heiko@rangun.de>
 *
 * This file is part of expr2cf.
 *
 * rational is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * rational is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with rational.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <iterator>
#include <cstdlib>
#include <sstream>
#include <ios>

#include <rational/gmp_rational.h>

int main(int argc, const char *argv[]) {

	try {

		Commons::Math::gmp_rational r;

		std::cin >> std::noskipws >> r;

		std::ostringstream os;

		Commons::Math::seq(r,
			std::ostream_iterator<Commons::Math::gmp_rational::integer_type>(os, ", "));

		std::cout << "[" << os.str().substr(0, os.str().length() - 2) << "]" << std::endl;

	} catch(const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
