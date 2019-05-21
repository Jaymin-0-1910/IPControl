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

#include <cstdio>
#include <fstream>
#include <string>

#include "exception.h"
#include "module.h"
#include "shared.h"

using namespace std;

bool Shared::fileExists(const string& path, bool checkRW) noexcept {
	return checkRW ? ofstream(path).is_open() : ifstream(path).is_open();
}

string Shared::getProperty(const string& key, const string& file) {
	ifstream propFile(file);

	if (!propFile.is_open()) {
		throw("Error occured while opening " + file);
	}

	for (string line; getline(propFile, line);) {
		if (line.compare(0, key.size(), key) == 0 && line[key.size()] == '=') {
			return line.substr(key.size() + 1);
		}
	}
	return "";
}

void Shared::setProperty(const string& key, const string& val, const string& file) {
	const string temp = Module::STORAGE + "/.tempfile";

	{
		ifstream propFile(file);
		ofstream tempFile(temp, ios::out | ios::trunc);

		if (!propFile.is_open()) {
			throw("Error occured while opening " + file);
		}
		if (!tempFile.is_open()) {
			throw("Error occured while opening " + temp);
		}

		for (string line; getline(propFile, line);) {
			if (line.compare(0, key.size(), key) == 0 && line[key.size()] == '=') {
				tempFile << key << '=' << val << "\n";
			} else {
				tempFile << line << "\n";
			}
		}
	}
	if (rename(temp.c_str(), file.c_str()) == -1) {
		throw("Error occured while moving " + temp + " to " + file);
	}
}
