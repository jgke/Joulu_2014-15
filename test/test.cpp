#include <iostream>

#include "test.hpp"

int success_count = 0;
int failure_count = 0;

void test_success(const char *name) {
    std::cout << "SUCCESS: " << name << std::endl;
    success_count++;
}

void test_failure(const char *name) {
    std::cout << "FAILURE: " << name << std::endl;
    failure_count++;
}

void test_true(const char *name, bool value) {
    value ? test_success(name) : test_failure(name);
}

void test_false(const char *name, bool value) {
    test_true(name, !value);
};

void print_test_status() {
    std::cout << "Test success rate: " << success_count << "/" <<
        success_count+failure_count << std::endl;
}
