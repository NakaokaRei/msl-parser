# MSL Parser

A Metal Shader Language parser implemented in C++17.

## Requirements

- CMake 3.16 or higher
- C++17 compatible compiler

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running Tests

```bash
cd build
ctest --output-on-failure
```

## Usage

The parser is built as a static library that can be integrated into your project:

```cpp
#include "msl_parser/lexer.h"

msl_parser::Lexer lexer("float4 position = float4(1.0);");
auto tokens = lexer.scanTokens();
```