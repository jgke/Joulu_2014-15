#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "common.hpp"
#include "handle.hpp"

void (*handler)(int sig);

#ifdef SENSIBLE_OS
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>
void handle(int sig, siginfo_t *siginfo, void *context) {
#else
void handle(int sig) {
#endif
    fprintf(stderr, "Caught signal %d.\n", sig);
    handler(sig);
}

void handle_signals(void (*cb)(int sig)) {
    handler = cb;
    const int ignore[] = {SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM};
    const int ignsize = sizeof(ignore)/sizeof(ignore[0]);
#ifdef SENSIBLE_OS
    struct sigaction act = {};
    act.sa_sigaction = &handle;
    act.sa_flags = SA_SIGINFO;
    for(int i = 0; i < ignsize; i++)
        if(sigaction(ignore[i], &act, NULL)) {
            std::cerr << "Failed to handle " << strsignal(ignore[i])
                << std::endl;
        exit(1);
    }
#else
    for(int i = 0; i < ignsize; i++)
        signal(ignore[i], handle);
#endif
}
