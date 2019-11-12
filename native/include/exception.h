/* Copyright (c) 2019 Jaymin Suthar. All rights reserved.
 *
 * This file is part of "Input Power Control (IPControl)".
 *
 * IPControl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, only version 3 of the License.
 *
 * IPControl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with IPControl.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <cerrno>
#include <cstring>
#include <string>

class Exception : public std::exception {
	public:
		Exception(const std::string &file, int line, const std::string &what) noexcept {
			using std::operator""s;

			_what = file.c_str() + ":"s + std::to_string(line) + ": " + what;
			if (errno != 0) {
				_what += " ("s + strerror(errno) + ")"s;
			}
		}

		~Exception() noexcept = default;

		const char *what() const noexcept {
			return _what.c_str();
		}

	private:
		std::string _what;
};

#define throw(err) (throw Exception(__FILE__, __LINE__, err))
