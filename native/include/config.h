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

namespace Config {
	bool isAutomated();
	int getThrDisable();
	int getThrEnable();

	std::string getTrigger();
	std::string getPosVal();
	std::string getNegVal();

	void setTrigger(const std::string& val);
	void setPosVal(const std::string& val);
	void setNegVal(const std::string& val);

	void toggleAutomation(const std::vector<std::string>& args);
	void updateThresholds(const std::vector<std::string>& args);
}
