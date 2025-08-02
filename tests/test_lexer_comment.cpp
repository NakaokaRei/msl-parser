#include <gtest/gtest.h>
#include "msl_parser/lexer.h"

using namespace msl_parser;

TEST(LexerTest, SingleLineComments) {
    // Comment at the beginning
    {
        Lexer lexer("// This is a comment\nint x = 5;");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 6);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::ASSIGN);
        EXPECT_EQ(tokens[3].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[4].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[5].type, TokenType::END_OF_FILE);
    }
    
    // Comment at the end of line
    {
        Lexer lexer("int x = 5; // Initialize x");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 6);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::ASSIGN);
        EXPECT_EQ(tokens[3].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[4].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[5].type, TokenType::END_OF_FILE);
    }
    
    // Multiple comments
    {
        Lexer lexer("// First comment\nint x; // Second comment\n// Third comment");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[3].type, TokenType::END_OF_FILE);
    }
    
    // Empty comment
    {
        Lexer lexer("//\nint x;");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[3].type, TokenType::END_OF_FILE);
    }
}

TEST(LexerTest, MultiLineComments) {
    // Simple multi-line comment
    {
        Lexer lexer("/* This is a comment */ int x;");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[3].type, TokenType::END_OF_FILE);
    }
    
    // Multi-line comment spanning lines
    {
        Lexer lexer("/* This is\n   a multi-line\n   comment */\nint x;");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[3].type, TokenType::END_OF_FILE);
    }
    
    // Comment in the middle of code
    {
        Lexer lexer("int /* type */ x /* variable */ = /* assignment */ 5;");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 6);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::ASSIGN);
        EXPECT_EQ(tokens[3].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[4].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[5].type, TokenType::END_OF_FILE);
    }
    
    // Star in comment
    {
        Lexer lexer("/* Comment with * star */ int x;");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[3].type, TokenType::END_OF_FILE);
    }
}

TEST(LexerTest, CommentsEdgeCases) {
    // Mixed single and multi-line comments
    {
        Lexer lexer("// Single line\n/* Multi\nline */ int x; // End comment");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[3].type, TokenType::END_OF_FILE);
    }
    
    // Comment-like content in string
    {
        Lexer lexer("\"// Not a comment\" /* Real comment */ \"/* Also not */\"");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 3);
        EXPECT_EQ(tokens[0].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "\"// Not a comment\"");
        EXPECT_EQ(tokens[1].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[1].lexeme, "\"/* Also not */\"");
        EXPECT_EQ(tokens[2].type, TokenType::END_OF_FILE);
    }
    
    // Division operator vs comment
    {
        Lexer lexer("int x = 10 / 2; // Division, not comment start");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 8);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::ASSIGN);
        EXPECT_EQ(tokens[3].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[4].type, TokenType::DIVIDE);
        EXPECT_EQ(tokens[5].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[6].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[7].type, TokenType::END_OF_FILE);
    }
}