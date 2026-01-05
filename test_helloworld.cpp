/**
 * Unit Tests for Hello World Program
 * Created by Claude Code
 */

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

// Include the functions to test (we'll link with helloworld.cpp)
#include "helloworld.h"

// Simple test framework macros
#define TEST(name) void test_##name()
#define RUN_TEST(name) do { \
    std::cout << "Running " << #name << "... "; \
    test_##name(); \
    std::cout << "PASSED" << std::endl; \
    tests_passed++; \
} while(0)

#define ASSERT_EQ(expected, actual) do { \
    if ((expected) != (actual)) { \
        std::cerr << "FAILED\n  Expected: " << (expected) \
                  << "\n  Actual: " << (actual) << std::endl; \
        tests_failed++; \
        return; \
    } \
} while(0)

#define ASSERT_TRUE(condition) do { \
    if (!(condition)) { \
        std::cerr << "FAILED\n  Condition was false" << std::endl; \
        tests_failed++; \
        return; \
    } \
} while(0)

#define ASSERT_FALSE(condition) do { \
    if (condition) { \
        std::cerr << "FAILED\n  Condition was true" << std::endl; \
        tests_failed++; \
        return; \
    } \
} while(0)

static int tests_passed = 0;
static int tests_failed = 0;

// Test: Default greeting returns expected string
TEST(get_greeting_returns_hello_world) {
    std::string result = get_greeting();
    ASSERT_EQ("Hello, World!", result);
}

// Test: Greeting is not empty
TEST(get_greeting_not_empty) {
    std::string result = get_greeting();
    ASSERT_FALSE(result.empty());
}

// Test: Personalized greeting with name
TEST(get_greeting_for_with_name) {
    std::string result = get_greeting_for("Alice");
    ASSERT_EQ("Hello, Alice!", result);
}

// Test: Personalized greeting with different name
TEST(get_greeting_for_with_different_name) {
    std::string result = get_greeting_for("Bob");
    ASSERT_EQ("Hello, Bob!", result);
}

// Test: Empty name falls back to default greeting
TEST(get_greeting_for_empty_name) {
    std::string result = get_greeting_for("");
    ASSERT_EQ("Hello, World!", result);
}

// Test: Greeting contains exclamation mark
TEST(get_greeting_contains_exclamation) {
    std::string result = get_greeting();
    ASSERT_TRUE(result.find('!') != std::string::npos);
}

// Test: Personalized greeting contains the name
TEST(get_greeting_for_contains_name) {
    std::string name = "Charlie";
    std::string result = get_greeting_for(name);
    ASSERT_TRUE(result.find(name) != std::string::npos);
}

// Test: Greeting starts with "Hello"
TEST(get_greeting_starts_with_hello) {
    std::string result = get_greeting();
    ASSERT_TRUE(result.substr(0, 5) == "Hello");
}

int main() {
    std::cout << "=== Hello World Unit Tests ===" << std::endl;
    std::cout << std::endl;

    RUN_TEST(get_greeting_returns_hello_world);
    RUN_TEST(get_greeting_not_empty);
    RUN_TEST(get_greeting_for_with_name);
    RUN_TEST(get_greeting_for_with_different_name);
    RUN_TEST(get_greeting_for_empty_name);
    RUN_TEST(get_greeting_contains_exclamation);
    RUN_TEST(get_greeting_for_contains_name);
    RUN_TEST(get_greeting_starts_with_hello);

    std::cout << std::endl;
    std::cout << "=== Test Summary ===" << std::endl;
    std::cout << "Passed: " << tests_passed << std::endl;
    std::cout << "Failed: " << tests_failed << std::endl;

    return tests_failed > 0 ? 1 : 0;
}
