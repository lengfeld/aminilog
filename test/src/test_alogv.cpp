/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld */

#define LOG_NDEBUG 0
#define LOG_TAG "test_alogv"

#include <log/log.h>

void test_alogv() {
    ALOGD("debug");
    ALOGV("verbose"); // Is printed, because of LOG_NDEBUG=1
}
