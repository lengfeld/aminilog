/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld */

// This header reimplements in the AOSP header file `log/log.h`. See
// https://cs.android.com/android/platform/superproject/+/android-11.0.0_r1:system/core/liblog/include/log/log.h

#pragma once

#include <android/log.h>
#include <log/log_main.h>

#if defined(__cplusplus)
extern "C" {
#endif

// Define LOG_TAG if not already defined by the developer.
#ifndef LOG_TAG
#define LOG_TAG NULL
#endif

#if defined(__cplusplus)
}
#endif
