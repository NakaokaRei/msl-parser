#include <gtest/gtest.h>
#include "msl_parser/lexer.h"

using namespace msl_parser;

TEST(LexerTest, ScanSingleInteger) {
    Lexer lexer("42");
    auto tokens = lexer.scanTokens();
    
    ASSERT_EQ(tokens.size(), 2);  // Number token + EOF
    EXPECT_EQ(tokens[0].type, TokenType::INTEGER_LITERAL);
    EXPECT_EQ(tokens[0].lexeme, "42");
    EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
}