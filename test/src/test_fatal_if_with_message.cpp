/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld */

#define LOG_TAG "test_fatal_if"

#include <log/log.h>

void test_fatal_if_with_message() {
    LOG_ALWAYS_FATAL_IF(false, "condition is false");
    LOG_ALWAYS_FATAL_IF(true, "condition is true");
    /* never reached */
}
