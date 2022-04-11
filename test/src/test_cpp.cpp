/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld */

#define LOG_TAG "test_cpp"

#include <log/log.h>

void test_function_cpp() {
    ALOGD("debug");
    ALOGI("info");
    ALOGW("warning");
    ALOGE("error");
    ALOGV("verbose"); // Is not printed because LOG_NDEBUG is not set
    LOG_ALWAYS_FATAL_IF(false);
    LOG_ALWAYS_FATAL_IF(false, "condition is false");

    ALOGD_IF(true, "debug if true");
    ALOGD_IF(false, "debug if false");
    ALOGI_IF(true, "info if true");
    ALOGI_IF(false, "info if false");
    ALOGE_IF(true, "error if true");
    ALOGE_IF(false, "error if false");
    ALOGV_IF(true, "verbose if true");  // Is not printed because LOG_NDEBUG is not set
    ALOGV_IF(false, "verbose if false"); // Is not printed because condition is false
}
