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

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "battery.h"
#include "daemon.h"
#include "exception.h"
#include "method.h"
#include "sanity.h"

using namespace std;
using namespace chrono;
using namespace this_thread;

enum {
	MODE_ENABLED,
	MODE_DISABLED
};

enum {
	THR_TYPE_LEVELED,
	THR_TYPE_TIMED
};

static Method::Info info;

static bool parseAndPopulate(const string &fmtStr) {
	switch (fmtStr[0]) {
		case 'e':
			info.mode = MODE_ENABLED;
			info.start = Daemon::requestEnabling;
			break;
		case 'd':
			info.mode = MODE_DISABLED;
			info.start = Daemon::requestDisabling;
			break;
		default: return false;
	}

	switch (fmtStr[1]) {
		case '%':
			info.type = THR_TYPE_LEVELED;
			info.value = Sanity::toLevel(fmtStr.substr(2));
			break;
		case 's':
			info.type = THR_TYPE_TIMED;
			info.value = stoi(fmtStr.substr(2));
			break;
		case 'm':
			info.type = THR_TYPE_TIMED;
			info.value = stoi(fmtStr.substr(2)) * 60;
			break;
		case 'h':
			info.type = THR_TYPE_TIMED;
			info.value = stoi(fmtStr.substr(2)) * 3600;
			break;
		default: return false;
	}
	return true;
}

void Method::parseAndRun(const vector<string> &args) {
	if (!parseAndPopulate(args[0])) {
		throw("Invalid format string: " + args[0]);
	}

	if (
			info.type == THR_TYPE_LEVELED
		&& (
				(Battery::getLevel() >= info.value && info.mode == MODE_ENABLED)
			|| (Battery::getLevel() <= info.value && info.mode == MODE_DISABLED)
		)
	) {
		throw("Unreachable target level: " + args[0].substr(2));
	}

	if (!info.start()) {
		throw("Another method is already running");
	}

	if (info.type == THR_TYPE_TIMED) {
		sleep_for(seconds(info.value));

	} else {
		while (Battery::getLevel() != info.value) {
			sleep_for(seconds(Sanity::SLEEP_DELAY));
		}
	}
	Daemon::requestAutomating();
}
