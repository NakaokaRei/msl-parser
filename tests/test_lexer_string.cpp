#include <gtest/gtest.h>
#include "msl_parser/lexer.h"

using namespace msl_parser;

TEST(LexerTest, BasicStringLiterals) {
    // Simple string
    {
        Lexer lexer("\"hello world\"");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "\"hello world\"");
        EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
    }
    
    // Empty string
    {
        Lexer lexer("\"\"");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "\"\"");
        EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
    }
    
    // Multiple strings
    {
        Lexer lexer("\"hello\" \"world\"");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 3);
        EXPECT_EQ(tokens[0].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "\"hello\"");
        EXPECT_EQ(tokens[1].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[1].lexeme, "\"world\"");
        EXPECT_EQ(tokens[2].type, TokenType::END_OF_FILE);
    }
    
    // String with spaces and punctuation
    {
        Lexer lexer("\"Hello, World! How are you?\"");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "\"Hello, World! How are you?\"");
        EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
    }
}

TEST(LexerTest, StringEscapeSequences) {
    // Newline escape
    {
        Lexer lexer("\"Hello\\nWorld\"");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "\"Hello\\nWorld\"");
        EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
    }
    
    // Tab escape
    {
        Lexer lexer("\"Hello\\tWorld\"");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "\"Hello\\tWorld\"");
        EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
    }
    
    // Escaped quote
    {
        Lexer lexer("\"Say \\\"Hello\\\" to the world\"");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "\"Say \\\"Hello\\\" to the world\"");
        EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
    }
    
    // Escaped backslash
    {
        Lexer lexer("\"Path: C:\\\\Program Files\\\\\"");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "\"Path: C:\\\\Program Files\\\\\"");
        EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
    }
    
    // Multiple escape sequences
    {
        Lexer lexer("\"Line 1\\nLine 2\\tTabbed\\\\Backslash\\\"Quote\"");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[0].lexeme, "\"Line 1\\nLine 2\\tTabbed\\\\Backslash\\\"Quote\"");
        EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
    }
}

TEST(LexerTest, StringInContext) {
    // String assignment
    {
        Lexer lexer("string message = \"Hello, World!\";");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 6);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);  // string
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);  // message
        EXPECT_EQ(tokens[2].type, TokenType::ASSIGN);
        EXPECT_EQ(tokens[3].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[3].lexeme, "\"Hello, World!\"");
        EXPECT_EQ(tokens[4].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[5].type, TokenType::END_OF_FILE);
    }
    
    // Function call with string
    {
        Lexer lexer("print(\"Error: \" + msg);");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 8);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);  // print
        EXPECT_EQ(tokens[1].type, TokenType::LEFT_PAREN);
        EXPECT_EQ(tokens[2].type, TokenType::STRING_LITERAL);
        EXPECT_EQ(tokens[2].lexeme, "\"Error: \"");
        EXPECT_EQ(tokens[3].type, TokenType::PLUS);
        EXPECT_EQ(tokens[4].type, TokenType::IDENTIFIER);  // msg
        EXPECT_EQ(tokens[5].type, TokenType::RIGHT_PAREN);
        EXPECT_EQ(tokens[6].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[7].type, TokenType::END_OF_FILE);
    }
}