/**
 * \file test.hpp
 * Test framework.
 */


#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <string>
#include <sstream>

/**
 * Defining will use alternative rendering and enables exceptions.
 */
#define DEBUG //so that classes throw

/**
 * Initialize tests.
 */
void init_tests();
/**
 * Print a successful test.
 * @param name name of the test
 */
void test_success(const char *name);
/**
 * Print a failed test.
 * @param name name of the test
 */
void test_failure(const char *name);
/**
 * Print a failed test, with a reason.
 * @param name name of the test
 * @param reason reason why the test failed
 */
void test_failure(const char *name, const char *reason);
/**
 * Test that is the value true.
 * @param name name of the test
 * @param value boolean to test
 */
void test_true(const char *name, bool value);
/**
 * Test that is the value false.
 * @param name name of the test
 * @param value boolean to test
 */
void test_false(const char *name, bool value);
/**
 * Test that are two values equal.
 * @param name name of the test
 * @param a expected value
 * @param b value to test
 */
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

/**
 * Test that does the piece of code run without throwing an exception.
 * @param name name of the test
 * @param func code to run
 */
#define NO_DEATH_TEST(name, func) \
    do { \
        try { \
            {func} \
            test_success(name); \
        } catch (...) { \
            test_failure(name); \
        } \
    } while(0) 

/**
 * Test that does the piece of code throw an exception.
 * @param name name of the test
 * @param func code to run
 */
#define DEATH_TEST(name, func) \
    do { \
        try { \
            {func} \
            test_failure(name); \
        } catch (...) { \
            test_success(name); \
        } \
    } while(0)

/**
 * Print status of the tests.
 */
void print_test_status();

#endif
