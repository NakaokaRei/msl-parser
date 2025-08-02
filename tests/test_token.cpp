#include <gtest/gtest.h>
#include "msl_parser/token.h"

using namespace msl_parser;

TEST(TokenTest, CreateToken) {
    Token token(TokenType::INTEGER_LITERAL, "42", 1, 5);
    
    EXPECT_EQ(token.type, TokenType::INTEGER_LITERAL);
    EXPECT_EQ(token.lexeme, "42");
    EXPECT_EQ(token.line, 1);
    EXPECT_EQ(token.column, 5);
}

TEST(TokenTest, TokenTypeToString) {
    EXPECT_STREQ(tokenTypeToString(TokenType::INTEGER_LITERAL), "INTEGER_LITERAL");
    EXPECT_STREQ(tokenTypeToString(TokenType::FLOAT_LITERAL), "FLOAT_LITERAL");
    EXPECT_STREQ(tokenTypeToString(TokenType::IDENTIFIER), "IDENTIFIER");
    EXPECT_STREQ(tokenTypeToString(TokenType::KERNEL), "KERNEL");
    EXPECT_STREQ(tokenTypeToString(TokenType::PLUS), "PLUS");
    EXPECT_STREQ(tokenTypeToString(TokenType::END_OF_FILE), "END_OF_FILE");
}