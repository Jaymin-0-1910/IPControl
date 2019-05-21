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

#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include "battery.h"
#include "config.h"
#include "exception.h"
#include "module.h"
#include "utility.h"

using namespace std;

static bool xfork() {
	switch (fork()) {
		case -1: throw("Error occured while forking child");
		case 0: return false;
		default: return true;
	}
}

void Utility::execDaemon(const vector<string>& args) {
	if (!xfork()) {
		setsid();

		if (xfork()) {
			exit(EXIT_SUCCESS);

		} else {
			const char* argv[args.size() + 1];
			argv[args.size()] = nullptr;

			for (int i = 0; i < args.size(); i++) {
				argv[i] = args[i].c_str();
			}
			if (execvp(Module::SELF_NAME_CLIENT.c_str(), (char* const*) argv) == -1) {
				throw("Error occured while replacing process");
			}
		}
	}
}

void Utility::printInfo(const vector<string>&) {
	cout << "Battery Information\n"
		<< "\n"
		<< "Level: " << Battery::getCapacity() << "\n"
		<< "Status: " << Battery::getStatus() << "\n"
		<< "\n"
		<< Module::ID << " Settings\n"
		<< "\n"
		<< "Automation: " << (Config::isAutomated() ? "Enabled" : "Disabled") << "\n"
		<< "Disable threshold: " << Config::getThrDisable() << "\n"
		<< "Enable threshold: " << Config::getThrEnable() << endl;

	exit(EXIT_SUCCESS);
}
