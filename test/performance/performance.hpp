#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include <cstdio>
#include <time.h>

#define GET_TIME(var) \
    do { \
        clock_gettime(CLOCK_MONOTONIC, &(var)); \
    } while(0);

#define PTEST(stream, name, n, count, func) \
    do { \
        struct timespec start; \
        struct timespec end; \
        GET_TIME(start); \
        for(int _i = 0; _i < (count); _i++) {\
            {func} \
        } \
        GET_TIME(end); \
        end.tv_sec -= start.tv_sec; \
        end.tv_nsec -= start.tv_nsec; \
        if(end.tv_nsec < 0) { \
            end.tv_nsec += 1000000000; \
            end.tv_sec -= 1; \
        } \
        end.tv_sec *= 1000; \
        end.tv_nsec *= 1000; \
        end.tv_sec /= (count); \
        end.tv_nsec /= (count); \
        fprintf((stream), "%d %ld.%09ld\n", (n), end.tv_sec, end.tv_nsec); \
    } while(0)

#endif
