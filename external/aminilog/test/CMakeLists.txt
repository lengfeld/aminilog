# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld

cmake_minimum_required(VERSION 3.10.2)

project(aminilogtest)

add_subdirectory(../ aminilog)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/test_c.c
    src/test_cpp.cpp
    src/test_fatal.cpp
    src/test_fatal_if.cpp
    src/test_fatal_if_with_message.cpp
    src/test_without_logtag.cpp
    src/test_alogv.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Werror -Wextra)

# The AOSP build system sets NDEBUG globally:
# https://cs.android.com/android/platform/superproject/+/master:build/soong/cc/config/global.go;l=41?q=NDEBUG&ss=android%2Fplatform%2Fsuperproject:build%2F
# This is needed to get the same behavior compared to AOSP code.
target_compile_definitions(${PROJECT_NAME} PUBLIC NDEBUG=1)

target_link_libraries(${PROJECT_NAME} PUBLIC aminilog)
