#include <gtest/gtest.h>
#include "msl_parser/lexer.h"

using namespace msl_parser;

TEST(LexerTest, ParenthesesBracesBrackets) {
    // Parentheses
    {
        Lexer lexer("()");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 3);
        EXPECT_EQ(tokens[0].type, TokenType::LEFT_PAREN);
        EXPECT_EQ(tokens[0].lexeme, "(");
        EXPECT_EQ(tokens[1].type, TokenType::RIGHT_PAREN);
        EXPECT_EQ(tokens[1].lexeme, ")");
        EXPECT_EQ(tokens[2].type, TokenType::END_OF_FILE);
    }
    
    // Braces
    {
        Lexer lexer("{}");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 3);
        EXPECT_EQ(tokens[0].type, TokenType::LEFT_BRACE);
        EXPECT_EQ(tokens[0].lexeme, "{");
        EXPECT_EQ(tokens[1].type, TokenType::RIGHT_BRACE);
        EXPECT_EQ(tokens[1].lexeme, "}");
        EXPECT_EQ(tokens[2].type, TokenType::END_OF_FILE);
    }
    
    // Brackets
    {
        Lexer lexer("[]");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 3);
        EXPECT_EQ(tokens[0].type, TokenType::LEFT_BRACKET);
        EXPECT_EQ(tokens[0].lexeme, "[");
        EXPECT_EQ(tokens[1].type, TokenType::RIGHT_BRACKET);
        EXPECT_EQ(tokens[1].lexeme, "]");
        EXPECT_EQ(tokens[2].type, TokenType::END_OF_FILE);
    }
    
    // Mixed delimiters
    {
        Lexer lexer("(){}[]");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 7);
        EXPECT_EQ(tokens[0].type, TokenType::LEFT_PAREN);
        EXPECT_EQ(tokens[1].type, TokenType::RIGHT_PAREN);
        EXPECT_EQ(tokens[2].type, TokenType::LEFT_BRACE);
        EXPECT_EQ(tokens[3].type, TokenType::RIGHT_BRACE);
        EXPECT_EQ(tokens[4].type, TokenType::LEFT_BRACKET);
        EXPECT_EQ(tokens[5].type, TokenType::RIGHT_BRACKET);
        EXPECT_EQ(tokens[6].type, TokenType::END_OF_FILE);
    }
}

TEST(LexerTest, Punctuation) {
    // Basic punctuation
    {
        Lexer lexer("; , .");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[0].lexeme, ";");
        EXPECT_EQ(tokens[1].type, TokenType::COMMA);
        EXPECT_EQ(tokens[1].lexeme, ",");
        EXPECT_EQ(tokens[2].type, TokenType::DOT);
        EXPECT_EQ(tokens[2].lexeme, ".");
        EXPECT_EQ(tokens[3].type, TokenType::END_OF_FILE);
    }
    
    // In context
    {
        Lexer lexer("foo.bar;");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 5);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].type, TokenType::DOT);
        EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[3].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[4].type, TokenType::END_OF_FILE);
    }
    
    // Function call with arguments
    {
        Lexer lexer("func(a, b, c);");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 10);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].type, TokenType::LEFT_PAREN);
        EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[3].type, TokenType::COMMA);
        EXPECT_EQ(tokens[4].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[5].type, TokenType::COMMA);
        EXPECT_EQ(tokens[6].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[7].type, TokenType::RIGHT_PAREN);
        EXPECT_EQ(tokens[8].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[9].type, TokenType::END_OF_FILE);
    }
}

TEST(LexerTest, MultiCharacterDelimiters) {
    // Arrow operator
    {
        Lexer lexer("->");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::ARROW);
        EXPECT_EQ(tokens[0].lexeme, "->");
        EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
    }
    
    // Scope resolution
    {
        Lexer lexer("::");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::SCOPE_RESOLUTION);
        EXPECT_EQ(tokens[0].lexeme, "::");
        EXPECT_EQ(tokens[1].type, TokenType::END_OF_FILE);
    }
    
    // Attribute brackets
    {
        Lexer lexer("[[ ]]");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 3);
        EXPECT_EQ(tokens[0].type, TokenType::ATTRIBUTE_LEFT);
        EXPECT_EQ(tokens[0].lexeme, "[[");
        EXPECT_EQ(tokens[1].type, TokenType::ATTRIBUTE_RIGHT);
        EXPECT_EQ(tokens[1].lexeme, "]]");
        EXPECT_EQ(tokens[2].type, TokenType::END_OF_FILE);
    }
    
    // In context
    {
        Lexer lexer("foo::bar->baz");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 6);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].type, TokenType::SCOPE_RESOLUTION);
        EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[3].type, TokenType::ARROW);
        EXPECT_EQ(tokens[4].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[5].type, TokenType::END_OF_FILE);
    }
    
    // Attributes with content
    {
        Lexer lexer("[[nodiscard]] int func();");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 9);
        EXPECT_EQ(tokens[0].type, TokenType::ATTRIBUTE_LEFT);
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].type, TokenType::ATTRIBUTE_RIGHT);
        EXPECT_EQ(tokens[3].type, TokenType::INT);
        EXPECT_EQ(tokens[4].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[5].type, TokenType::LEFT_PAREN);
        EXPECT_EQ(tokens[6].type, TokenType::RIGHT_PAREN);
        EXPECT_EQ(tokens[7].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[8].type, TokenType::END_OF_FILE);
    }
}