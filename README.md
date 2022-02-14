# aminilog library – AOSP styled logging macros for NDK projects

The `aminilog` library is a header only library providing logging macros
for NDK projects. The macros are identical to the macros used in the AOSP.

If you want to start writing C/C++ code in an Android app that eventually
becomes AOSP code or if you are working primarily in the AOSP codebase and want
the same macros in your new NDK based C++ project or if you do not want to
write macros for yourself, this library is for you.

The goal is to have 100% compatibility to the AOSP style logging macros, provided
by [liblog](https://cs.android.com/android/platform/superproject/+/master:system/logging/liblog/).
Compiling the code against the NDK or against the liblog library should result
in the same runtime behavior.


# How to use the library in your app

For now the library is a header only library. Just clone, unpack or copy the
files from the git repository into your app's project, e.g. into a folder called
`external/aminilog`.

Then add the library to your cmake build, by adding the line

    add_subdirectory(../../external/aminilog aminilog)

into your `CMakeLists.txt`. You mostly have to adapt the path.
Additionally you should add

    target_compile_definitions(${PROJECT_NAME} PUBLIC NDEBUG=1)

to your definitions. Setting `NDEBUG` will disable all `ALOGV` log messages by
default which is also the standard behavior in AOSP code.

If you want to use the logging macros in a C/C++ source file, add the
following at the very beginning of the file.

    //#define LOG_NDEBUG 0
    #define LOG_TAG "your_log_tag"

Further below add the following include header

    #include <log/log.h>

After that the code in that file can use the logging macros:

    ALOGD("debug message %d", some_int);
    ALOGI("info: %s (%d)", some_string, some_int);
    ALOGW("warning message");
    ALOGE("error message");

    // If NDEBUG is defined, ALOGV message are *not* logged.
    // They are just removed from the source code.
    ALOGV("verbose message");
    // They can be temporarly enabled defining LOG_NDEBUG. See
    // the comment at the top of the file.

To add an assert, you can use

    LOG_ALWAYS_FATAL_IF(pointer == NULL);
    LOG_ALWAYS_FATAL_IF(i >= 20, "array index out of range: i = %d", i);
    LOG_ALWAYS_FATAL("This code should never be reached");

For more examples, have a look the AOSP code itself or at the testcases in
[test/src/](test/src/). All available macros are documented in the AOSP liblog's
[README.md](https://cs.android.com/android/platform/superproject/+/master:system/logging/liblog/README.md)
file.


# Releases

There are no releases yet. Just use the current version on the `main` branch.

# License

This project is licensed under the [MIT License](https://spdx.org/licenses/MIT.html).
See also the file [LICENSE](LICENSE).


# Contributions

Contributions, e.g. to extend the available macros, are welcome. Open a
merge/pull request or send a patch. Just use my email address from the commits.


# Header setup and usage

Just some random information. No interesting for users!

The header file `android/log.h` is available in the AOSP and slightly different
in the NDK.

Most AOSP code just includes the hader `log/log.h` to get access to the logging
macros. It's including all the other headers:

    // snipped:
    #include <android/log.h>
    #include <log/log_id.h>
    #include <log/log_main.h>
    #include <log/log_radio.h>
    #include <log/log_read.h>
    #include <log/log_safetynet.h>
    #include <log/log_system.h>
    #include <log/log_time.h>

See [system/core/liblog/include/log/log.h](https://cs.android.com/android/platform/superproject/+/android-11.0.0_r1:system/core/liblog/include/log/log.h)

Nearly no AOSP code includes the `log/log_*.h` files directly.
