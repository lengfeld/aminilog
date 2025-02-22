/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld */

#define LOG_TAG "test_fatal_if"

#include <log/log.h>

void test_fatal_if() {
    LOG_ALWAYS_FATAL_IF(1 == 2);
    LOG_ALWAYS_FATAL_IF(2 == 2);
    /* never reached */
}
