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

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "commandline.h"
#include "config.h"
#include "daemon.h"
#include "exception.h"
#include "method.h"
#include "module.h"
#include "setup.h"
#include "utility.h"

using namespace std;

static const array<Commandline::Option, 7> option = { {
	{ "--update",	0,	2,	true,	Config::updateThresholds },
	{ "--toggle",	1,	1,	true,	Config::toggleAutomation },
	{ "--method",	1,	1,	true,	Method::parseAndRun },
	{ "--daemon",	1,	1,	false,	Daemon::handleArgs },
	{ "--info",		0,	0,	true,	Utility::printInfo },
	{ "--help",		0,	0,	false,	Module::printHelp }
} };

static const char** argvMain;

static int optIndex;
static int argIndex;
static int argcMain;

static bool setOptIndexOf(const char* arg) noexcept {
	optIndex = -1;

	for (int i = 0; i < option.size(); i++) {
		if (option[i].key == arg) {
			optIndex = i;
		}
	}
	return optIndex != -1;
}

static bool populateArgs(vector<string>& args) {
	for (int i = argIndex + 1; i < argcMain && argvMain[i]; i++) {

		if (argvMain[i][0] == '-' && argvMain[i][1] == '-') {
			break;
		}
		if (args.size() < option[optIndex].argMax) {
			args.push_back(argvMain[i]);
			argIndex++;
		}
	}
	return args.size() >= option[optIndex].argMin;
}

bool Commandline::handleArgs(int argc, const char* argv[]) noexcept {
	argcMain = argc;
	argvMain = argv;

	for (argIndex = 1; argIndex < argcMain; argIndex++) {
		try {
			vector<string> args;

			if (!setOptIndexOf(argvMain[argIndex])) {
				throw("Unrecognized option: "s + argvMain[argIndex]);
			}
			if (!populateArgs(args)) {
				throw("Option [" + option[optIndex].key + "] is missing arguments");
			}
			if (option[optIndex].sanitize) {
				Setup::checkAndSanitize();
			}

			option[optIndex].handler(args);
			cout << "Option [" << option[optIndex].key << "] handled successfully!" << endl;

		} catch (const exception& e) {
			cerr << e.what() << endl;
			return false;
		}
	}
	return true;
}
