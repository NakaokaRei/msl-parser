cmake_minimum_required(VERSION 3.16)
project(msl_parser VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(include)

# Library source files
set(LIB_SOURCES
    src/lexer.cpp
    src/parser.cpp
    src/ast.cpp
    src/token.cpp
    src/error.cpp
)

# Create static library
add_library(msl_parser STATIC ${LIB_SOURCES})
target_include_directories(msl_parser PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Example executable
add_executable(msl_parser_example examples/main.cpp)
target_link_libraries(msl_parser_example PRIVATE msl_parser)

# Installation rules
install(TARGETS msl_parser
    EXPORT msl_parser_targets
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/msl_parser DESTINATION include)

# Export targets
install(EXPORT msl_parser_targets
    FILE msl_parser_config.cmake
    NAMESPACE msl_parser::
    DESTINATION lib/cmake/msl_parser
)

# Enable testing
enable_testing()

# Add tests subdirectory
add_subdirectory(tests)