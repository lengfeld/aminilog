/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld */

// This header reimplements in the AOSP header file `log/log_main.h`. See
// https://cs.android.com/android/platform/superproject/+/android-11.0.0_r1:system/core/liblog/include/log/log_main.h

#pragma once

#include <stdbool.h>

#include <android/log.h>


#if defined(__cplusplus)
extern "C" {
#endif


// The developer can enable or disable the ALOGV messages in the file by
// defining LOG_NDEBUG beforehand.
#ifndef LOG_NDEBUG
#ifdef NDEBUG
#define LOG_NDEBUG 1
#else
#define LOG_NDEBUG 0
#endif
#endif

#define aminilog_print_log(prio, tag, ...)  __android_log_print(prio, tag, __VA_ARGS__)

#define aminilog_vprint_log(prio, cond, tag, ...) __android_log_vprint(prio, tag, __VA_ARGS__)


#ifndef ALOG
#define ALOG(priority, tag, ...) (aminilog_print_log(priority, tag, __VA_ARGS__))
#endif


#if LOG_NDEBUG
// Do not fully strip the log statement via the preprocessor from the code, to
// still see compile errors and warnings.
#define ALOGV(...)                                     \
  do {                                                 \
    if (false) {                                       \
      ALOG(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__); \
    }                                                  \
  } while (false)
#else
#define ALOGV(...) ALOG(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#endif

#ifndef ALOGD
#define ALOGD(...) ALOG(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#endif

#ifndef ALOGI
#define ALOGI(...) ALOG(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#endif

#ifndef ALOGW
#define ALOGW(...) ALOG(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#endif

#ifndef ALOGE
#define ALOGE(...) ALOG(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif

#ifndef ALOGF
#define ALOGF(...) ALOG(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)
#endif

#ifndef LOG_ALWAYS_FATAL_IF
#define LOG_ALWAYS_FATAL_IF(cond, ...)                             \
  do {                                                             \
    if (cond) {                                                    \
      __android_log_assert(#cond, LOG_TAG, ##__VA_ARGS__, NULL); \
    }                                                              \
  } while (false)

#endif

#ifndef LOG_ALWAYS_FATAL
#define LOG_ALWAYS_FATAL(...) __android_log_assert(NULL, LOG_TAG, ##__VA_ARGS__)
#endif


#if defined(__cplusplus)
}
#endif
