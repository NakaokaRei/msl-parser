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

TEST(LexerTest, ScanFloatLiterals) {
    // Simple float
    {
        Lexer lexer("3.14");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "3.14");
    }
    
    // Float with f suffix
    {
        Lexer lexer("1.0f");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "1.0f");
    }
    
    // Scientific notation
    {
        Lexer lexer("2.5e-3");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "2.5e-3");
    }
    
    // Float without fractional part
    {
        Lexer lexer("10.");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "10.");
    }
}

TEST(LexerTest, ScanHexadecimalLiterals) {
    // Simple hex
    {
        Lexer lexer("0xFF");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "0xFF");
    }
    
    // Lowercase hex
    {
        Lexer lexer("0x1234abcd");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "0x1234abcd");
    }
    
    // Mixed case
    {
        Lexer lexer("0xDeAdBeEf");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "0xDeAdBeEf");
    }
}

TEST(LexerTest, ScanBinaryLiterals) {
    // Simple binary
    {
        Lexer lexer("0b1010");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "0b1010");
    }
    
    // Longer binary
    {
        Lexer lexer("0b11111111");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "0b11111111");
    }
}

TEST(LexerTest, NumericLiteralEdgeCases) {
    // Multiple numbers with spaces
    {
        Lexer lexer("42 3.14 0xFF");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "42");
        EXPECT_EQ(tokens[1].type, TokenType::FLOAT_LITERAL);
        EXPECT_EQ(tokens[1].lexeme, "3.14");
        EXPECT_EQ(tokens[2].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[2].lexeme, "0xFF");
    }
    
    // Scientific notation variations
    {
        Lexer lexer("1e10");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "1e10");
    }
    
    {
        Lexer lexer("3.14e+5");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "3.14e+5");
    }
    
    // Zero prefix cases
    {
        Lexer lexer("0");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "0");
    }
    
    // Float with h suffix (half precision)
    {
        Lexer lexer("1.5h");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "1.5h");
    }
}