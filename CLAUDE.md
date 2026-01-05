# CLAUDE.md

Instructions for Claude Code when working with this C++ repository.

## Before Submitting a PR

### Code Quality
- Ensure code compiles without errors or warnings (`g++ -Wall -Wextra -Werror`)
- Follow consistent naming conventions (snake_case for variables/functions, PascalCase for classes)
- Remove any debug print statements or commented-out code
- Keep functions focused and under 50 lines where possible

### Memory Management
- Check for memory leaks (use smart pointers where appropriate)
- Ensure all allocated memory is properly freed
- Avoid raw pointers when `std::unique_ptr` or `std::shared_ptr` suffice

### Testing
- Run all existing tests before submitting
- Add unit tests for new functionality
- Verify edge cases are handled

### Documentation
- Add comments for complex logic
- Update header file documentation for public APIs
- Include example usage for new functions

### Build Verification
```bash
# Compile with strict warnings
g++ -Wall -Wextra -Werror -std=c++17 *.cpp -o program

# Run the program to verify basic functionality
./program
```

### Style Guidelines
- Use 4 spaces for indentation (no tabs)
- Keep lines under 100 characters
- Use `#pragma once` or include guards in headers
- Prefer `const` and `constexpr` where applicable
