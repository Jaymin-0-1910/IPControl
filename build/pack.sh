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

readonly ZIPNAME=IPControl-$VERSION-$CODE-stable

readonly TEMPZIP=$OUTDIR/$ZIPNAME.tempfile
readonly OUTZIP=$OUTDIR/$ZIPNAME-signed.zip

readonly ZIPSIGNER=$BUILDDIR/zipsigner.jar

function makezip {
	if ! cd $2; then
		abort "Error occured while changing working directory to $2"
	fi
	find . -type f | while read FILE; do
		zip -u9q $1 $FILE
	done
}

function signzip {
	java -jar $ZIPSIGNER $1 $2
}

rm -f $TEMPZIP $OUTZIP

print "Packing recovery flashable zip"
makezip $TEMPZIP $MODULE

print "Signing the zip using test keys"
signzip $TEMPZIP $OUTZIP
