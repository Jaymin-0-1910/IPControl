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

readonly BINDIR=$MODULE/bin
readonly OUTBIN=$BINDIR/ipc_\$1

readonly NDK_BINDIR=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin

readonly API_LEVEL=21

readonly ARM_TRIPLE=armv7a-linux-androideabi$API_LEVEL
readonly X86_TRIPLE=i686-linux-android$API_LEVEL

readonly ARM_COMPILER=$NDK_BINDIR/$ARM_TRIPLE-clang++
readonly X86_COMPILER=$NDK_BINDIR/$X86_TRIPLE-clang++

if [[ $BUILD_TYPE == test ]]; then
	readonly MACROS=(
		-D__TEST_BUILD
	)
fi

readonly CFLAGS=(
	-std=c++17 -O2 -fno-rtti -fomit-frame-pointer -ffunction-sections -fdata-sections -flto
)

readonly LDLIBS=(
	-L$NATIVE/lib -lsocket++_\$1 -Wl,--gc-sections -static
)

function compile {
	eval $2 ${MACROS[@]} *.cc -Iinclude ${CFLAGS[@]} ${LDLIBS[@]} -s -o $OUTBIN

	if (($? != 0)); then
		abort "Error occured while compiling"
	fi
}

if ! cd $NATIVE; then
	abort "Error occured while changing working directory to $NATIVE"
fi

print "Compiling ipc binary for arm"
compile arm $ARM_COMPILER

print "Compiling ipc binary for x86"
compile x86 $X86_COMPILER
