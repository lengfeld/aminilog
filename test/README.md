# Tests for aminilog

This directory contains a testsuite for the aminilog library.  The basic idea
is compile a test program

* against the aminilog library in the NDK/SDK and
* a second time against the original `liblog` library from the AOSP.

Both binaries, one from the SDK and the other from the AOSP, should produce the
same logcat output and behave identically.


# How to run them?

To execute the tests you need

* to clone the repository into an AOSP tree. For example into the folder
  `external/`,
* to have an x86_64 emulator mostly the same version as the AOSP tree running
  and
* to have the Android SDK with NDK available in the environment.

Then you can execute the commands to build and run the tests:

    $ . build/envsetup.sh
    $ lunch aosp_x86_64-eng
    $ cd external/aminilog/test/
    $ make build-sdk
    $ make build-aosp

    # for smoke testing
    $ make run-sdk
    $ make run-aosp

    # To run the testcases for the SDK and the AOSP binary
    $ make tests

If you see the message `All tests successful!` on the console,
all tests were successful.
