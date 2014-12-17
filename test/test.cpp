#include <iostream>

#include "test.hpp"

void test_success(const char *name) {
    std::cout << "SUCCESS: " << name << std::endl;
}

void test_failure(const char *name) {
    std::cout << "FAILURE: " << name << std::endl;
}

void test_true(const char *name, bool value) {
    value ? test_success(name) : test_failure(name);
}

void test_false(const char *name, bool value) {
    test_true(name, !value);
};
