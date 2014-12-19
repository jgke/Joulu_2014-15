#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <string>
#include <sstream>

void init_tests();
void test_success(const char *name);
void test_failure(const char *name);
void test_failure(const char *name, const char *reason);
void test_true(const char *name, bool value);
void test_false(const char *name, bool value);
void print_test_status();
template <class T> void test_equal(const char *name, T a, T b) {
    if(a == b)
        test_success(name);
    else {
        std::stringstream sstream;
        sstream << "expected ";
        sstream << a;
        sstream << ", got ";
        sstream << b;
        test_failure(name, sstream.str().c_str());
    }
}

#define NO_DEATH_TEST(name, func) \
    do { \
        try { \
            {func} \
            test_success(name); \
        } catch (...) { \
            test_failure(name); \
        } \
    } while(0) 

#define DEATH_TEST(name, func) \
    do { \
        try { \
            {func} \
            test_failure(name); \
        } catch (...) { \
            test_success(name); \
        } \
    } while(0)

#endif
