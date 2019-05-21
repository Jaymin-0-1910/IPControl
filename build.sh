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

SCRIPT_NAME=$(basename $BASH_SOURCE)

readonly PROJECT=$(dirname $(realpath $BASH_SOURCE))

readonly NATIVE=$PROJECT/native
readonly MODULE=$PROJECT/module

readonly OUTDIR=$PROJECT/out

readonly LOGFILE=$OUTDIR/build.log

readonly BUILDDIR=$PROJECT/build
readonly BUILDER=$BUILDDIR/build.sh

readonly BUILD_TYPE=$1

mkdir $OUTDIR 2>/dev/null
exec 3>&2 2>$LOGFILE

function abort {
	echo >&3 -e "$SCRIPT_NAME: \e[01;33mERROR:\e[0m \e[01;31m$1\e[0m"
	source $BUILDDIR/clean.sh
	exit 1
}

if [[ ! -d $ANDROID_NDK_HOME ]]; then
	abort "Please export Android NDK path to ANDROID_NDK_HOME variable"
fi
if ! command -v java >/dev/null; then
	abort "Please install \"java\" command to PATH"
fi
if ! command -v zip >/dev/null; then
	abort "Please install \"zip\" command to PATH"
fi

source $BUILDER

echo -e "\nResulting zip file: \e[01;32m$OUTZIP\e[0m"
