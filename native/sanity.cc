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

#include <string>

#include "exception.h"
#include "sanity.h"

using namespace std;

static const int LEVEL_MIN = 0;
static const int LEVEL_MAX = 100;

int Sanity::toLevel(const string& lvlStr) {
	int level = stoi(lvlStr);

	return level < LEVEL_MIN || level > LEVEL_MAX
		? throw("Out of range level: " + lvlStr)
		: level;
}
