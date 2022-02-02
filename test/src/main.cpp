/* SPDX-License-Identifier: MIT */
/* SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld */

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

extern void test_function_cpp();
extern "C" void test_function_c();
extern void test_fatal();
extern void test_fatal_if();
extern void test_fatal_if_with_message();
extern void test_without_logtag();
extern void test_alogv();

int main(int argc, char **argv) {
    bool do_fatal = false;
    bool do_fatal_if = false;
    bool do_fatal_if_with_message = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "fatal") == 0)
            do_fatal = true;
        else if (strcmp(argv[i], "fatal_if") == 0)
            do_fatal_if = true;
        else if (strcmp(argv[i], "fatal_if_with_message") == 0)
            do_fatal_if_with_message = true;
    }

    printf("%d\n", getpid());
    fflush(stdout); // otherwise it's not printed if the program aborts

    if (do_fatal) {
        test_fatal();
    } else if (do_fatal_if) {
        test_fatal_if();
    } else if (do_fatal_if_with_message) {
        test_fatal_if_with_message();
    } else {
        test_function_cpp();
        test_function_c();
        test_without_logtag();
        test_alogv();
    }
    return 0;
}
