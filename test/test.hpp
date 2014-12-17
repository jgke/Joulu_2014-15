#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>

void test_true(const char *name, bool value);
void test_false(const char *name, bool value);
template <class T> void test_equal(const char *name, T a, T b) {
    test_true(name, a == b);
}

#endif
