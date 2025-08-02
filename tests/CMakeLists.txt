# Google Test setup
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

# Test sources
set(TEST_SOURCES
    test_token.cpp
    test_lexer.cpp
)

# Create test executable
add_executable(msl_parser_tests ${TEST_SOURCES})

# Link with library and Google Test
target_link_libraries(msl_parser_tests
    PRIVATE
    msl_parser
    gtest_main
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(msl_parser_tests)