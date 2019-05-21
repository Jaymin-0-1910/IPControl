#!/usr/bin/env bash

# Copyright (c) 2019 Jaymin Suthar. All rights reserved.
#
# This file is part of "Input Power Control (IPControl)".
#
# IPControl is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, only version 3 of the License.
#
# IPControl is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with IPControl.  If not, see <https://www.gnu.org/licenses/>.

readonly ANDROID_NDK=$ANDROID_NDK_HOME

readonly MODINFO=$MODULE/module.prop

readonly BUILD_STEPPERS=(
	$BUILDDIR/patch.sh
	$BUILDDIR/compile.sh
	$BUILDDIR/pack.sh
	$BUILDDIR/clean.sh
)

function print {
	echo -e "\e[01;34m- $1\e[0m"
}

function getprop {
	sed -n "s/^$1=//p" $2
}

readonly VERSION=$(getprop version $MODINFO)
readonly CODE=$(($(getprop versionCode $MODINFO) + 1))

sed -i "s/^versionCode=.*/versionCode=$CODE/g" $MODINFO
sed -i "s/__VERSION_CODE__/$CODE/g" $NATIVE/module.cc

for BUILD_STEPPER in ${BUILD_STEPPERS[@]}; do
	source $BUILD_STEPPER
done
