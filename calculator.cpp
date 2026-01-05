/**
 *   ██████╗██╗      █████╗ ██╗   ██╗██████╗ ███████╗
 *  ██╔════╝██║     ██╔══██╗██║   ██║██╔══██╗██╔════╝
 *  ██║     ██║     ███████║██║   ██║██║  ██║█████╗
 *  ██║     ██║     ██╔══██║██║   ██║██║  ██║██╔══╝
 *  ╚██████╗███████╗██║  ██║╚██████╔╝██████╔╝███████╗
 *   ╚═════╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝
 *   ██████╗ ██████╗ ██████╗ ███████╗
 *  ██╔════╝██╔═══██╗██╔══██╗██╔════╝
 *  ██║     ██║   ██║██║  ██║█████╗
 *  ██║     ██║   ██║██║  ██║██╔══╝
 *  ╚██████╗╚██████╔╝██████╔╝███████╗
 *   ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝
 *
 * Simple Calculator - Supports +, -, *, / and parentheses
 * Created by Claude Code
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <sstream>
#include <vector>
#include <functional>

/**
 * Calculator class that parses and evaluates mathematical expressions
 * using recursive descent parsing.
 *
 * Supports:
 *   - Addition (+)
 *   - Subtraction (-)
 *   - Multiplication (*)
 *   - Division (/)
 *   - Parentheses ()
 *   - Negative numbers
 *   - Decimal numbers
 */
class Calculator {
public:
    /**
     * Evaluate a mathematical expression string
     * @param expression The expression to evaluate (e.g., "2 + 3 * 4")
     * @return The result of the expression
     * @throws std::runtime_error if the expression is invalid
     */
    double evaluate(const std::string& expression) {
        expr_ = expression;
        pos_ = 0;
        skip_whitespace();

        if (pos_ >= expr_.length()) {
            throw std::runtime_error("Empty expression");
        }

        double result = parse_expression();
        skip_whitespace();

        if (pos_ < expr_.length()) {
            throw std::runtime_error("Unexpected character: " +
                                     std::string(1, expr_[pos_]));
        }

        return result;
    }

private:
    std::string expr_;
    size_t pos_;

    void skip_whitespace() {
        while (pos_ < expr_.length() && std::isspace(expr_[pos_])) {
            pos_++;
        }
    }

    char peek() const {
        if (pos_ >= expr_.length()) {
            return '\0';
        }
        return expr_[pos_];
    }

    char consume() {
        return expr_[pos_++];
    }

    /**
     * Parse expression: handles addition and subtraction (lowest precedence)
     */
    double parse_expression() {
        double left = parse_term();

        while (true) {
            skip_whitespace();
            char op = peek();

            if (op == '+') {
                consume();
                skip_whitespace();
                left = left + parse_term();
            } else if (op == '-') {
                consume();
                skip_whitespace();
                left = left - parse_term();
            } else {
                break;
            }
        }

        return left;
    }

    /**
     * Parse term: handles multiplication and division (higher precedence)
     */
    double parse_term() {
        double left = parse_factor();

        while (true) {
            skip_whitespace();
            char op = peek();

            if (op == '*') {
                consume();
                skip_whitespace();
                left = left * parse_factor();
            } else if (op == '/') {
                consume();
                skip_whitespace();
                double divisor = parse_factor();
                if (divisor == 0) {
                    throw std::runtime_error("Division by zero");
                }
                left = left / divisor;
            } else {
                break;
            }
        }

        return left;
    }

    /**
     * Parse factor: handles parentheses, unary minus, and numbers
     */
    double parse_factor() {
        skip_whitespace();
        char c = peek();

        // Handle unary minus
        if (c == '-') {
            consume();
            skip_whitespace();
            return -parse_factor();
        }

        // Handle unary plus
        if (c == '+') {
            consume();
            skip_whitespace();
            return parse_factor();
        }

        // Handle parentheses
        if (c == '(') {
            consume();
            skip_whitespace();
            double result = parse_expression();
            skip_whitespace();

            if (peek() != ')') {
                throw std::runtime_error("Missing closing parenthesis");
            }
            consume();
            return result;
        }

        // Handle numbers
        return parse_number();
    }

    /**
     * Parse a number (integer or decimal)
     */
    double parse_number() {
        skip_whitespace();
        size_t start = pos_;

        // Parse integer part
        while (pos_ < expr_.length() && std::isdigit(expr_[pos_])) {
            pos_++;
        }

        // Parse decimal part
        if (pos_ < expr_.length() && expr_[pos_] == '.') {
            pos_++;
            while (pos_ < expr_.length() && std::isdigit(expr_[pos_])) {
                pos_++;
            }
        }

        if (start == pos_) {
            throw std::runtime_error("Expected number at position " +
                                     std::to_string(pos_));
        }

        return std::stod(expr_.substr(start, pos_ - start));
    }
};

// Unit test framework
struct TestResult {
    std::string name;
    bool passed;
    std::string message;
};

class TestRunner {
public:
    void add_test(const std::string& name, std::function<void()> test) {
        tests_.push_back({name, test});
    }

    void run_all() {
        int passed = 0;
        int failed = 0;

        std::cout << "\n";
        std::cout << "╔════════════════════════════════════════════════════════╗\n";
        std::cout << "║           CALCULATOR UNIT TESTS - Claude Code          ║\n";
        std::cout << "╚════════════════════════════════════════════════════════╝\n\n";

        for (const auto& test : tests_) {
            std::cout << "Running: " << test.first << " ... ";
            try {
                test.second();
                std::cout << "PASSED\n";
                passed++;
            } catch (const std::exception& e) {
                std::cout << "FAILED: " << e.what() << "\n";
                failed++;
            }
        }

        std::cout << "\n";
        std::cout << "════════════════════════════════════════════════════════\n";
        std::cout << "Results: " << passed << " passed, " << failed << " failed\n";
        std::cout << "════════════════════════════════════════════════════════\n";

        if (failed > 0) {
            exit(1);
        }
    }

private:
    std::vector<std::pair<std::string, std::function<void()>>> tests_;
};

void assert_equal(double expected, double actual, const std::string& msg = "") {
    const double epsilon = 1e-9;
    if (std::abs(expected - actual) > epsilon) {
        std::ostringstream oss;
        oss << "Expected " << expected << " but got " << actual;
        if (!msg.empty()) {
            oss << " (" << msg << ")";
        }
        throw std::runtime_error(oss.str());
    }
}

void assert_throws(std::function<void()> func, const std::string& msg = "") {
    bool threw = false;
    try {
        func();
    } catch (...) {
        threw = true;
    }
    if (!threw) {
        throw std::runtime_error("Expected exception but none thrown" +
                                 (msg.empty() ? "" : ": " + msg));
    }
}

void run_tests() {
    TestRunner runner;
    Calculator calc;

    // Basic arithmetic tests
    runner.add_test("Addition: 2 + 3", [&]() {
        assert_equal(5.0, calc.evaluate("2 + 3"));
    });

    runner.add_test("Subtraction: 10 - 4", [&]() {
        assert_equal(6.0, calc.evaluate("10 - 4"));
    });

    runner.add_test("Multiplication: 6 * 7", [&]() {
        assert_equal(42.0, calc.evaluate("6 * 7"));
    });

    runner.add_test("Division: 15 / 3", [&]() {
        assert_equal(5.0, calc.evaluate("15 / 3"));
    });

    // Operator precedence tests
    runner.add_test("Precedence: 2 + 3 * 4", [&]() {
        assert_equal(14.0, calc.evaluate("2 + 3 * 4"));
    });

    runner.add_test("Precedence: 10 - 6 / 2", [&]() {
        assert_equal(7.0, calc.evaluate("10 - 6 / 2"));
    });

    runner.add_test("Precedence: 2 * 3 + 4 * 5", [&]() {
        assert_equal(26.0, calc.evaluate("2 * 3 + 4 * 5"));
    });

    // Parentheses tests
    runner.add_test("Parentheses: (2 + 3) * 4", [&]() {
        assert_equal(20.0, calc.evaluate("(2 + 3) * 4"));
    });

    runner.add_test("Parentheses: 2 * (3 + 4)", [&]() {
        assert_equal(14.0, calc.evaluate("2 * (3 + 4)"));
    });

    runner.add_test("Nested parentheses: ((2 + 3) * (4 + 5))", [&]() {
        assert_equal(45.0, calc.evaluate("((2 + 3) * (4 + 5))"));
    });

    runner.add_test("Complex: (1 + 2) * (3 + 4) / (5 - 3)", [&]() {
        assert_equal(10.5, calc.evaluate("(1 + 2) * (3 + 4) / (5 - 3)"));
    });

    // Decimal number tests
    runner.add_test("Decimals: 3.14 + 2.86", [&]() {
        assert_equal(6.0, calc.evaluate("3.14 + 2.86"));
    });

    runner.add_test("Decimals: 10.5 / 2.1", [&]() {
        assert_equal(5.0, calc.evaluate("10.5 / 2.1"));
    });

    // Negative number tests
    runner.add_test("Negative: -5 + 3", [&]() {
        assert_equal(-2.0, calc.evaluate("-5 + 3"));
    });

    runner.add_test("Negative: 5 * -3", [&]() {
        assert_equal(-15.0, calc.evaluate("5 * -3"));
    });

    runner.add_test("Double negative: --5", [&]() {
        assert_equal(5.0, calc.evaluate("--5"));
    });

    // Whitespace handling tests
    runner.add_test("Whitespace: spaces around operators", [&]() {
        assert_equal(10.0, calc.evaluate("  5   +   5  "));
    });

    runner.add_test("Whitespace: no spaces", [&]() {
        assert_equal(10.0, calc.evaluate("5+5"));
    });

    // Edge cases
    runner.add_test("Single number: 42", [&]() {
        assert_equal(42.0, calc.evaluate("42"));
    });

    runner.add_test("Zero: 0 + 0", [&]() {
        assert_equal(0.0, calc.evaluate("0 + 0"));
    });

    // Error handling tests
    runner.add_test("Error: Division by zero", [&]() {
        assert_throws([&]() { calc.evaluate("5 / 0"); });
    });

    runner.add_test("Error: Missing closing parenthesis", [&]() {
        assert_throws([&]() { calc.evaluate("(5 + 3"); });
    });

    runner.add_test("Error: Empty expression", [&]() {
        assert_throws([&]() { calc.evaluate(""); });
    });

    runner.add_test("Error: Invalid character", [&]() {
        assert_throws([&]() { calc.evaluate("5 + a"); });
    });

    runner.run_all();
}

void interactive_mode() {
    Calculator calc;
    std::string input;

    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║         CALCULATOR - Created by Claude Code            ║\n";
    std::cout << "║  Supports: +, -, *, /, and parentheses ()              ║\n";
    std::cout << "║  Type 'quit' or 'exit' to quit                         ║\n";
    std::cout << "║  Type 'test' to run unit tests                         ║\n";
    std::cout << "╚════════════════════════════════════════════════════════╝\n\n";

    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, input);

        if (input == "quit" || input == "exit") {
            std::cout << "Goodbye!\n";
            break;
        }

        if (input == "test") {
            run_tests();
            continue;
        }

        if (input.empty()) {
            continue;
        }

        try {
            double result = calc.evaluate(input);
            std::cout << "= " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    // If --test flag is provided, run tests and exit
    if (argc > 1 && std::string(argv[1]) == "--test") {
        run_tests();
        return 0;
    }

    // Otherwise, run interactive mode
    interactive_mode();
    return 0;
}
