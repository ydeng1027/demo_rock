/**
 * Hello World Program in C++
 * Created by Claude Code
 */

#include <iostream>
#include <string>
#include "helloworld.h"

std::string get_greeting() {
    return "Hello, World!";
}

std::string get_greeting_for(const std::string& name) {
    if (name.empty()) {
        return get_greeting();
    }
    return "Hello, " + name + "!";
}

int main() {
    std::cout << get_greeting() << std::endl;
    return 0;
}
