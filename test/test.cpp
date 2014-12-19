#include <iostream>

//sigsegv handling
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "test.hpp"

int success_count = 0;
int failure_count = 0;

void handle(int sig, siginfo_t *siginfo, void *context) {
    void *trace[10];
    size_t len = backtrace(trace, sizeof(trace)/sizeof(trace[0]));
    fprintf(stderr, "SIGSEGV on test\n");
    backtrace_symbols_fd(trace, len, STDERR_FILENO);
    exit(1);
}

void init_tests() {
    struct sigaction act;
    act.sa_sigaction = &handle;
    act.sa_flags = SA_SIGINFO;
    if(sigaction(SIGSEGV, &act, NULL)) {
        std::cerr << "Failed to handle sigsegv." << std::endl;
        exit(1);
    }
}

void test_success(const char *name) {
    std::cout << "SUCCESS: " << name << std::endl;
    success_count++;
}

void test_failure(const char *name) {
    std::cout << "FAILURE: " << name << std::endl;
    failure_count++;
}

void test_failure(const char *name, const char *reason) {
    std::cout << "FAILURE: " << name << " (" << reason << ")" << std::endl;
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
