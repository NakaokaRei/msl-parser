#include <gtest/gtest.h>
#include "msl_parser/lexer.h"

using namespace msl_parser;

TEST(LexerTest, ArithmeticOperators) {
    // Basic arithmetic operators
    {
        Lexer lexer("+ - * / %");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 6);
        EXPECT_EQ(tokens[0].type, TokenType::PLUS);
        EXPECT_EQ(tokens[0].lexeme, "+");
        EXPECT_EQ(tokens[1].type, TokenType::MINUS);
        EXPECT_EQ(tokens[1].lexeme, "-");
        EXPECT_EQ(tokens[2].type, TokenType::MULTIPLY);
        EXPECT_EQ(tokens[2].lexeme, "*");
        EXPECT_EQ(tokens[3].type, TokenType::DIVIDE);
        EXPECT_EQ(tokens[3].lexeme, "/");
        EXPECT_EQ(tokens[4].type, TokenType::MODULO);
        EXPECT_EQ(tokens[4].lexeme, "%");
    }
    
    // Arithmetic in expression
    {
        Lexer lexer("a + b - c * d / e % f");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 12);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].type, TokenType::PLUS);
        EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[3].type, TokenType::MINUS);
        EXPECT_EQ(tokens[4].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[5].type, TokenType::MULTIPLY);
        EXPECT_EQ(tokens[6].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[7].type, TokenType::DIVIDE);
        EXPECT_EQ(tokens[8].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[9].type, TokenType::MODULO);
        EXPECT_EQ(tokens[10].type, TokenType::IDENTIFIER);
    }
    
    // Increment/decrement operators
    {
        Lexer lexer("++ --");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 3);
        EXPECT_EQ(tokens[0].type, TokenType::PLUS_PLUS);
        EXPECT_EQ(tokens[0].lexeme, "++");
        EXPECT_EQ(tokens[1].type, TokenType::MINUS_MINUS);
        EXPECT_EQ(tokens[1].lexeme, "--");
    }
}

TEST(LexerTest, CompoundAssignmentOperators) {
    // Compound assignment operators
    {
        Lexer lexer("+= -= *= /= %=");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 6);
        EXPECT_EQ(tokens[0].type, TokenType::PLUS_ASSIGN);
        EXPECT_EQ(tokens[0].lexeme, "+=");
        EXPECT_EQ(tokens[1].type, TokenType::MINUS_ASSIGN);
        EXPECT_EQ(tokens[1].lexeme, "-=");
        EXPECT_EQ(tokens[2].type, TokenType::MULTIPLY_ASSIGN);
        EXPECT_EQ(tokens[2].lexeme, "*=");
        EXPECT_EQ(tokens[3].type, TokenType::DIVIDE_ASSIGN);
        EXPECT_EQ(tokens[3].lexeme, "/=");
        EXPECT_EQ(tokens[4].type, TokenType::MODULO_ASSIGN);
        EXPECT_EQ(tokens[4].lexeme, "%=");
    }
    
    // Basic assignment
    {
        Lexer lexer("a = 5");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].type, TokenType::ASSIGN);
        EXPECT_EQ(tokens[1].lexeme, "=");
        EXPECT_EQ(tokens[2].type, TokenType::INTEGER_LITERAL);
    }
}

TEST(LexerTest, ComparisonOperators) {
    // Comparison operators
    {
        Lexer lexer("== != < > <= >=");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 7);
        EXPECT_EQ(tokens[0].type, TokenType::EQUAL);
        EXPECT_EQ(tokens[0].lexeme, "==");
        EXPECT_EQ(tokens[1].type, TokenType::NOT_EQUAL);
        EXPECT_EQ(tokens[1].lexeme, "!=");
        EXPECT_EQ(tokens[2].type, TokenType::LESS_THAN);
        EXPECT_EQ(tokens[2].lexeme, "<");
        EXPECT_EQ(tokens[3].type, TokenType::GREATER_THAN);
        EXPECT_EQ(tokens[3].lexeme, ">");
        EXPECT_EQ(tokens[4].type, TokenType::LESS_EQUAL);
        EXPECT_EQ(tokens[4].lexeme, "<=");
        EXPECT_EQ(tokens[5].type, TokenType::GREATER_EQUAL);
        EXPECT_EQ(tokens[5].lexeme, ">=");
    }
}

TEST(LexerTest, LogicalAndBitwiseOperators) {
    // Logical operators
    {
        Lexer lexer("&& || !");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::AND);
        EXPECT_EQ(tokens[0].lexeme, "&&");
        EXPECT_EQ(tokens[1].type, TokenType::OR);
        EXPECT_EQ(tokens[1].lexeme, "||");
        EXPECT_EQ(tokens[2].type, TokenType::NOT);
        EXPECT_EQ(tokens[2].lexeme, "!");
    }
    
    // Bitwise operators
    {
        Lexer lexer("& | ^ ~ << >>");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 7);
        EXPECT_EQ(tokens[0].type, TokenType::BITWISE_AND);
        EXPECT_EQ(tokens[0].lexeme, "&");
        EXPECT_EQ(tokens[1].type, TokenType::BITWISE_OR);
        EXPECT_EQ(tokens[1].lexeme, "|");
        EXPECT_EQ(tokens[2].type, TokenType::BITWISE_XOR);
        EXPECT_EQ(tokens[2].lexeme, "^");
        EXPECT_EQ(tokens[3].type, TokenType::BITWISE_NOT);
        EXPECT_EQ(tokens[3].lexeme, "~");
        EXPECT_EQ(tokens[4].type, TokenType::LEFT_SHIFT);
        EXPECT_EQ(tokens[4].lexeme, "<<");
        EXPECT_EQ(tokens[5].type, TokenType::RIGHT_SHIFT);
        EXPECT_EQ(tokens[5].lexeme, ">>");
    }
    
    // Ternary operator parts
    {
        Lexer lexer("? :");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 3);
        EXPECT_EQ(tokens[0].type, TokenType::QUESTION);
        EXPECT_EQ(tokens[0].lexeme, "?");
        EXPECT_EQ(tokens[1].type, TokenType::COLON);
        EXPECT_EQ(tokens[1].lexeme, ":");
    }
}

TEST(LexerTest, OperatorEdgeCases) {
    // Complex expression with multiple operators
    {
        Lexer lexer("a += b << 2 && c >= d || !e");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 13);  // Including EOF token
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].type, TokenType::PLUS_ASSIGN);
        EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[3].type, TokenType::LEFT_SHIFT);
        EXPECT_EQ(tokens[4].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[5].type, TokenType::AND);
        EXPECT_EQ(tokens[6].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[7].type, TokenType::GREATER_EQUAL);
        EXPECT_EQ(tokens[8].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[9].type, TokenType::OR);
        EXPECT_EQ(tokens[10].type, TokenType::NOT);
        EXPECT_EQ(tokens[11].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[12].type, TokenType::END_OF_FILE);
    }
    
    // Operators without spaces
    {
        Lexer lexer("a+b*c-d/e%f");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 12);  // Including EOF token
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].type, TokenType::PLUS);
        EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[3].type, TokenType::MULTIPLY);
        EXPECT_EQ(tokens[4].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[5].type, TokenType::MINUS);
        EXPECT_EQ(tokens[6].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[7].type, TokenType::DIVIDE);
        EXPECT_EQ(tokens[8].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[9].type, TokenType::MODULO);
        EXPECT_EQ(tokens[10].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[11].type, TokenType::END_OF_FILE);
    }
    
    // Ternary operator expression
    {
        Lexer lexer("a ? b : c");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 6);  // Including EOF token
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].type, TokenType::QUESTION);
        EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[3].type, TokenType::COLON);
        EXPECT_EQ(tokens[4].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[5].type, TokenType::END_OF_FILE);
    }
    
    // Increment/decrement in expression
    {
        Lexer lexer("++a + b--");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 6);  // Including EOF token
        EXPECT_EQ(tokens[0].type, TokenType::PLUS_PLUS);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::PLUS);
        EXPECT_EQ(tokens[3].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[4].type, TokenType::MINUS_MINUS);
        EXPECT_EQ(tokens[5].type, TokenType::END_OF_FILE);
    }
}