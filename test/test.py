#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld

# Small script to copy a binary to the target device, execute it, and compare
# the exit code and logcat output with a reference value.  It's self made
# integration test system.
#
# The first argument is the path to the binary, the other arguments are passed
# to the binary on execution.

import sys
from os.path import join
from subprocess import Popen, PIPE, DEVNULL


TARGET_TEMP_DIR = "/data/local/tmp/"


def get_logcat_from_pid(pid):
    p = Popen(["adb", "logcat", "-v", "tag", "-d", "--pid", str(pid)],
              shell=False, stdout=PIPE)
    stdout, _ = p.communicate()
    if p.returncode != 0:
        raise Exception("Cannot execute logcat")

    utf8_output = stdout.decode("utf8")
    utf8_output = utf8_output.replace(str(pid), "XXXX")
    return utf8_output


def run(binary, args):
    prog_on_device = join(TARGET_TEMP_DIR, "prog")
    p = Popen(["adb", "push", binary, prog_on_device], shell=False)
    x = p.communicate()
    if p.returncode != 0:
        raise Exception("Cannot push binary to device")

    # For now we ignore the output of stderr. It actually contains the abort
    # condition for the fatal macro.
    p = Popen(["adb", "shell", prog_on_device] + args,
              stdout=PIPE, stderr=DEVNULL)

    stdout, _ = p.communicate()

    # Parse pid from stdout
    pid = int(stdout)
    if not pid > 0:
        raise ValueError("Cannot get pid from stdout buffer:", stdout)

    ret = p.returncode

    logcat = get_logcat_from_pid(pid)

    return ret, logcat


TEST_CASES = [
    ("Testing macros", [], 0,
"""--------- beginning of main
D/test_cpp: debug
I/test_cpp: info
W/test_cpp: warning
E/test_cpp: error
D/test_c  : debug
I/test_c  : info
W/test_c  : warning
E/test_c  : error
D/prog    : debug
I/prog    : info
W/prog    : warning
E/prog    : error
D/test_alogv: debug
V/test_alogv: verbose
"""),

    ("Testing LOG_ALWAYS_FATAL macro", ["fatal"], 134,
"""--------- beginning of main
F/test_fatal: message d = 42
--------- beginning of crash
F/libc    : Fatal signal 6 (SIGABRT), code -1 (SI_QUEUE) in tid XXXX (prog), pid XXXX (prog)
"""),

    ("Testing LOG_ALWAYS_FATAL_IF macro", ["fatal_if"], 134,
"""--------- beginning of main
F/test_fatal_if: Assertion failed: 2 == 2
--------- beginning of crash
F/libc    : Fatal signal 6 (SIGABRT), code -1 (SI_QUEUE) in tid XXXX (prog), pid XXXX (prog)
"""),

    ("Testing LOG_ALWAYS_FATAL_IF macro with message", ["fatal_if_with_message"], 134,
"""--------- beginning of main
F/test_fatal_if: condition is true
--------- beginning of crash
F/libc    : Fatal signal 6 (SIGABRT), code -1 (SI_QUEUE) in tid XXXX (prog), pid XXXX (prog)
"""),
]


def main():
    binary = sys.argv[1]

    failed = False
    for name, args, exit_code_expected, logcat_expected in TEST_CASES:
        print("Running test:", name)
        ret, logcat = run(binary, args)

        print("Exit code: %d" % (ret,))

        logcat_with_indent = "\n".join("    " + line for line in logcat.rstrip("\n").split("\n"))
        print("logcat: \n%s" % (logcat_with_indent,))

        if ret != exit_code_expected or logcat != logcat_expected:
            print("-> Failed")
            failed = True
        else:
            print("-> Success!")
        print()

    print()
    if failed:
        print("At least one test has failed!")
        return 1

    print("All tests successful!")
    return 0


if __name__ == "__main__":
    sys.exit(main())
