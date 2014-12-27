#include <iostream>
#include <cstdio>

#include "common.hpp"

#ifdef SENSIBLE_OS
#include <execinfo.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#endif

#include "handle.hpp"

#include "test.hpp"

int success_count = 0;
int failure_count = 0;

void handler(int sig) {
#ifdef SENSIBLE_OS
    void *trace[10];
    size_t len = backtrace(trace, sizeof(trace)/sizeof(trace[0]));
    fprintf(stderr, "Signal %d(%s) while testing\n", sig, strsignal(sig));
    backtrace_symbols_fd(trace, len, STDERR_FILENO);
#else
    fprintf(stderr, "Signal %d while testing\n", sig);
#endif
    exit(1);
}

void init_tests() {
    handle_signals(&handler);
}

void test_success(const char *name) {
    std::cout << "\033[32mSUCCESS: \033[0m" << name << std::endl;
    success_count++;
}

void test_failure(const char *name) {
    std::cout << "\033[31mFAILURE: \033[0m" << name << std::endl;
    failure_count++;
}

void test_failure(const char *name, const char *reason) {
    std::cout << "\033[31mFAILURE: \033[0m" << name
        << " (" << reason << ")" << std::endl;
    failure_count++;
}


void test_true(const char *name, bool value) {
    value ? test_success(name) : test_failure(name, "expected true, got false");
}

void test_false(const char *name, bool value) {
    value ? test_failure(name, "expected false, got true") : test_success(name);
};

void print_test_status() {
    std::cout << "Test success rate: " << success_count << "/" <<
        success_count+failure_count << std::endl;
}
