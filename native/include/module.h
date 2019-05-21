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

#include <string>
#include <vector>

namespace Module {
	const std::string ID = "IPControl";
	const std::string MOUNTPATH = "/data/adb/modules";
	const std::string STORAGE = MOUNTPATH + "/" + ID;

	const std::string SELF_NAME_CLIENT = "ipc";
	const std::string SELF_NAME_DAEMON = "ipcd";

	const std::string HELP =
		"Usage: `ipc [<option> [<args>...]...]`\n"
		"\n"
		"Options:\n"
		"\n"
		"[-u] <thr_disable> <thr_enable>\n"
		"\n"
		"    Updates disable and enable threshold for Automation.\n"
		"    resets them to defaults if no values were specified.\n"
		"    <thr_disable> and <thr_enable> must be integers.\n"
		"\n"
		"    -> `ipc -u 90 80` sets disable threshold to 90 and\n"
		"                      enable threshold to 80\n"
		"    -> `ipc -u`       resets thresholds to 70 60\n"
		"\n"
		"[-t] <status>\n"
		"\n"
		"    Toggles Automation on or off.\n"
		"    <status> can be 'ON' or 'OFF'.\n"
		"\n"
		"    -> `ipc -t ON`  toggles Automation on\n"
		"    -> `ipc -t OFF` toggles Automation off\n"
		"\n"
		"[-m] <format_str>\n"
		"\n"
		"    Run a method based on format string <format_str>.\n"
		"    Here, format string must follow the pattern:\n"
		"        (e|d)(%|s|m|h)(threshold: int)\n"
		"\n"
		"    where...\n"
		"    ... (e|d)     defines if enable/disabling charging,\n"
		"    ... (%|s|m|h) defines if seeking level or timespan,\n"
		"    ...           and this is the value of threshold.\n"
		"\n"
		"    -> `ipc -m es60` enables charging for 60 seconds\n"
		"    -> `ipc -m d%40` disables charging until 40%\n"
		"    -> `ipc -m em30` enables charging for 30 minutes\n"
		"\n"
		"[-d] <action>\n"
		"\n"
		"    Launches or kills the daemon.\n"
		"    <action> can be 'launch' or 'kill'.\n"
		"\n"
		"    -> `ipc -d launch` launches the daemon\n"
		"    -> `ipc -d kill`   kills the daemon\n"
		"\n"
		"[-i]\n"
		"\n"
		"    Print battery details and IPControl settings.\n"
		"\n"
		"    -> `ipc -i` prints battery level, charging status,\n"
		"                Automation status, disable threshold\n"
		"                and enable threshold";

	[[noreturn]] void printHelp(const std::vector<std::string>&) noexcept;
}
