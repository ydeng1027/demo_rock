/**
 * Hello World Header
 * Created by Claude Code
 */

#pragma once

#include <string>

/**
 * Returns the default greeting message.
 * @return "Hello, World!"
 */
std::string get_greeting();

/**
 * Returns a personalized greeting message.
 * @param name The name to greet (if empty, returns default greeting)
 * @return Greeting string in format "Hello, {name}!"
 */
std::string get_greeting_for(const std::string& name);
