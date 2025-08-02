# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Metal Shader Language (MSL) parser implemented in C++ following Test-Driven Development (TDD) practices. The project is structured as a static library that can be integrated into other projects.

## Build Commands

```bash
# Configure and build
mkdir -p build
cd build
cmake ..
cmake --build .

# Run tests
ctest --output-on-failure

# Run specific test
./tests/msl_parser_tests --gtest_filter=TokenTest.CreateToken

# Run example
./msl_parser_example
```

## Architecture

The parser follows a traditional compiler frontend architecture:

1. **Lexer** (`include/msl_parser/lexer.h`, `src/lexer.cpp`): Tokenizes the input Metal Shader Language source code into a stream of tokens
2. **Parser** (`src/parser.cpp`): Will build an Abstract Syntax Tree (AST) from the token stream
3. **AST** (`src/ast.cpp`): Will represent the program structure
4. **Error Handling** (`src/error.cpp`): Will manage parsing errors and diagnostics

The project is organized to be used as a library:
- Headers in `include/msl_parser/` are public API
- Implementation in `src/` is internal
- Static library `libmsl_parser.a` is generated for linking

## Development Workflow

**IMPORTANT: This project strictly follows Test-Driven Development (TDD) methodology. All new features and modifications MUST follow this process:**

1. **RED**: Write a failing test first that describes the desired behavior
2. **GREEN**: Implement the minimal code necessary to make the test pass
3. **REFACTOR**: Improve the code while keeping all tests passing

Never write implementation code before having a failing test. This ensures all code is tested and the design emerges from actual requirements.

## Testing

Tests use Google Test 1.15.2 and are located in `tests/`. Each component has its corresponding test file:
- `test_token.cpp` - Token structure tests
- `test_lexer.cpp` - Lexer functionality tests