#include <iostream>

#include "common.hpp" //SENSIBLE_OS

#ifdef SENSIBLE_OS
//sigsegv handling
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#endif

#include "test.hpp"

int success_count = 0;
int failure_count = 0;

#ifdef SENSIBLE_OS
void handle(int sig, siginfo_t *siginfo, void *context) {
    void *trace[10];
    size_t len = backtrace(trace, sizeof(trace)/sizeof(trace[0]));
    fprintf(stderr, "Signal %d(%s) while testing\n", sig, strsignal(sig));
    backtrace_symbols_fd(trace, len, STDERR_FILENO);
    exit(1);
}
#else
void handle(int sig) {
    fprintf(stderr, "Signal %d(%s) while testing\n", sig, strsignal(sig));
    exit(1);
}
#endif

void init_tests() {
#ifdef SENSIBLE_OS
    struct sigaction act = {};
    act.sa_sigaction = &handle;
    act.sa_flags = SA_SIGINFO;
    if(sigaction(SIGSEGV, &act, NULL)) {
        std::cerr << "Failed to handle sigsegv." << std::endl;
        exit(1);
    }
    if(sigaction(SIGABRT, &act, NULL)) {
        std::cerr << "Failed to handle sigabrt." << std::endl;
        exit(1);
    }
#else
    if(signal(SIGSEGV, handle)) {
        std::cerr << "Failed to handle sigsegv." << std::endl;
        exit(1);
    }
    if(signal(SIGABRT, handle)) {
        std::cerr << "Failed to handle sigabrt." << std::endl;
        exit(1);
    }
#endif
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
