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

#include "config.h"
#include "daemon.h"
#include "database.h"
#include "exception.h"
#include "setup.h"
#include "shared.h"

static void detectSwitch() {
	for (const Database::Switch& switch_ : Database::getSwitchDB()) {
		if (Shared::fileExists(switch_.trigger, true)) {
			Config::setTrigger(switch_.trigger);
			Config::setPosVal(switch_.posVal);
			Config::setNegVal(switch_.negVal);
			return;
		}
	}
	throw("Your device is unfortunately not supported :(");
}

void Setup::checkAndSanitize() {
	if (!Shared::fileExists(Config::getTrigger(), true)) {
		detectSwitch();
	}
	if (!Daemon::isRunning()) {
		Daemon::handleArgs({ "launch" });
	}
}
