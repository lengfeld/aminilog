/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld */

#define LOG_TAG "test_fatal"

#include <log/log.h>

void test_fatal() {
    LOG_ALWAYS_FATAL("message d = %d", 42);
    /* never reached */
}
