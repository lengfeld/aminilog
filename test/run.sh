#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld

# Small script to copy the test binary to a target device, execute it and print
# it's logcat messages.

set -x

TARGET_TEMP_DIR=/data/local/tmp/

binary=$1
shift

if [ ! -x "$binary" ]; then
    echo "Binary does not exists or is not executable!"
    exit 1
fi

adb push $binary ${TARGET_TEMP_DIR}/prog
pid=$(adb shell ${TARGET_TEMP_DIR}/prog $@)
exit_code=$?

echo pid = $pid
echo exit_code = $exit_code

adb logcat -d --pid $pid | sed '/beginning of main/d' | cut -c 32-
