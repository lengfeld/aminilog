/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld */

// This testcase does not have a LOG_TAG defined here!

#include <log/log.h>

void test_without_logtag() {
    ALOGD("debug");
    ALOGI("info");
    ALOGW("warning");
    ALOGE("error");
    LOG_ALWAYS_FATAL_IF(false);
    LOG_ALWAYS_FATAL_IF(false, "condition is false");
}
