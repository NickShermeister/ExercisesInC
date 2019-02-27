/* Code to test a function in util.c for Software Systems 2019 at Olin College of Engineering

Nicholas Sherman
February 28, 2019

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "miniunit.h"
#include "util.c" //I still don't understand why i have to include util.c and i can't include util.h?
#include "trout.h"

typedef struct timeval Timeval;
int tests_run = 0;

static char *test1() {
    struct timeval out;
    struct timeval in;
    out.tv_usec =500000;
    out.tv_sec = 10;
    in.tv_usec =100000;
    in.tv_sec = 0;
    tv_sub(&out, &in);
    // printf("%i\n", out.tv_usec);
    char *message = "test1 failed: tv_sub(\"500000us\", \"100000us\") should return 400000us";
    mu_assert(message, out.tv_usec == 400000);
    return NULL;
}

static char *test2() {
    struct timeval out;
    struct timeval in;
    out.tv_sec = 156;
    out.tv_usec = 0;
    in.tv_sec = 5;
    in.tv_usec = 100000;
    tv_sub(&out, &in);
    // printf("%i\n", out.tv_usec);
    char *message = "test2 failed: tv_sub(\"156s\", \"5s, 100000us\") should return 150s";
    mu_assert(message, out.tv_sec == 150);
    return NULL;
}

static char *test3() {
    struct timeval out;
    struct timeval in;
    out.tv_sec = 10;
    out.tv_usec = 100000;
    in.tv_sec = 100;
    in.tv_usec = 100000;

    tv_sub(&out, &in);
    // printf("%i\n", out.tv_sec);
    char *message = "test1 failed: endswith(\"10s, 100000us\", \"100s, 100000\") should return -90s";
    mu_assert(message, out.tv_sec == -90);
    return NULL;
}



static char * all_tests() {
    mu_run_test(test1);
    mu_run_test(test2);
    mu_run_test(test3);
    return NULL;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
