/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld */

#define LOG_TAG "test_c"

#include <log/log.h>

void test_function_c() {
    ALOGD("debug");
    ALOGI("info");
    ALOGW("warning");
    ALOGE("error");
    ALOGV("verbose"); // Is not printed because LOG_NDEBUG is not set
    LOG_ALWAYS_FATAL_IF(false);
    LOG_ALWAYS_FATAL_IF(false, "condition is false");
}
