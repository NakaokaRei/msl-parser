#include <gtest/gtest.h>
#include "msl_parser/lexer.h"

using namespace msl_parser;

TEST(LexerTest, ScanIdentifiers) {
    // Simple identifier
    {
        Lexer lexer("position");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[0].lexeme, "position");
    }
    
    // Identifier with numbers
    {
        Lexer lexer("vertex1");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[0].lexeme, "vertex1");
    }
    
    // Identifier with underscore
    {
        Lexer lexer("_private_var");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 2);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[0].lexeme, "_private_var");
    }
    
    // Multiple identifiers
    {
        Lexer lexer("foo bar baz");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[0].lexeme, "foo");
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].lexeme, "bar");
        EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].lexeme, "baz");
    }
}

TEST(LexerTest, ScanKeywords) {
    // Basic type keywords
    {
        Lexer lexer("void int float bool");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 5);
        EXPECT_EQ(tokens[0].type, TokenType::VOID);
        EXPECT_EQ(tokens[0].lexeme, "void");
        EXPECT_EQ(tokens[1].type, TokenType::INT);
        EXPECT_EQ(tokens[1].lexeme, "int");
        EXPECT_EQ(tokens[2].type, TokenType::FLOAT);
        EXPECT_EQ(tokens[2].lexeme, "float");
        EXPECT_EQ(tokens[3].type, TokenType::BOOL);
        EXPECT_EQ(tokens[3].lexeme, "bool");
    }
    
    // Control flow keywords
    {
        Lexer lexer("if else return");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::IF);
        EXPECT_EQ(tokens[0].lexeme, "if");
        EXPECT_EQ(tokens[1].type, TokenType::ELSE);
        EXPECT_EQ(tokens[1].lexeme, "else");
        EXPECT_EQ(tokens[2].type, TokenType::RETURN);
        EXPECT_EQ(tokens[2].lexeme, "return");
    }
    
    // Metal-specific keywords
    {
        Lexer lexer("kernel vertex fragment device constant");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 6);
        EXPECT_EQ(tokens[0].type, TokenType::KERNEL);
        EXPECT_EQ(tokens[0].lexeme, "kernel");
        EXPECT_EQ(tokens[1].type, TokenType::VERTEX);
        EXPECT_EQ(tokens[1].lexeme, "vertex");
        EXPECT_EQ(tokens[2].type, TokenType::FRAGMENT);
        EXPECT_EQ(tokens[2].lexeme, "fragment");
        EXPECT_EQ(tokens[3].type, TokenType::DEVICE);
        EXPECT_EQ(tokens[3].lexeme, "device");
        EXPECT_EQ(tokens[4].type, TokenType::CONSTANT);
        EXPECT_EQ(tokens[4].lexeme, "constant");
    }
    
    // Keywords vs identifiers
    {
        Lexer lexer("int integer");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 3);
        EXPECT_EQ(tokens[0].type, TokenType::INT);
        EXPECT_EQ(tokens[0].lexeme, "int");
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].lexeme, "integer");
    }
}

TEST(LexerTest, IdentifierKeywordEdgeCases) {
    // Mixed identifiers, keywords, and numbers
    {
        Lexer lexer("float4 position = float4(1.0);");
        auto tokens = lexer.scanTokens();
        
        // Now includes = operator, parentheses, dot, and semicolon
        ASSERT_EQ(tokens.size(), 9);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT4);  // float4 is now a keyword
        EXPECT_EQ(tokens[0].lexeme, "float4");
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].lexeme, "position");
        EXPECT_EQ(tokens[2].type, TokenType::ASSIGN);
        EXPECT_EQ(tokens[2].lexeme, "=");
        EXPECT_EQ(tokens[3].type, TokenType::FLOAT4);
        EXPECT_EQ(tokens[3].lexeme, "float4");
        EXPECT_EQ(tokens[4].type, TokenType::LEFT_PAREN);
        EXPECT_EQ(tokens[4].lexeme, "(");
        EXPECT_EQ(tokens[5].type, TokenType::FLOAT_LITERAL);
        EXPECT_EQ(tokens[5].lexeme, "1.0");
        EXPECT_EQ(tokens[6].type, TokenType::RIGHT_PAREN);
        EXPECT_EQ(tokens[6].lexeme, ")");
        EXPECT_EQ(tokens[7].type, TokenType::SEMICOLON);
        EXPECT_EQ(tokens[7].lexeme, ";");
        EXPECT_EQ(tokens[8].type, TokenType::END_OF_FILE);
    }
    
    // Underscore variations
    {
        Lexer lexer("_foo foo_ _foo_ __foo__");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 5);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[0].lexeme, "_foo");
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[1].lexeme, "foo_");
        EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[2].lexeme, "_foo_");
        EXPECT_EQ(tokens[3].type, TokenType::IDENTIFIER);
        EXPECT_EQ(tokens[3].lexeme, "__foo__");
    }
    
    // Case sensitivity
    {
        Lexer lexer("INT Int int");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);  // INT is not same as int
        EXPECT_EQ(tokens[0].lexeme, "INT");
        EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);  // Int is not same as int
        EXPECT_EQ(tokens[1].lexeme, "Int");
        EXPECT_EQ(tokens[2].type, TokenType::INT);         // int is keyword
        EXPECT_EQ(tokens[2].lexeme, "int");
    }
}

TEST(LexerTest, VectorAndMatrixTypes) {
    // Vector types
    {
        Lexer lexer("float2 float3 float4 int2 int3 int4 uint2 uint3 uint4");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 10);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT2);
        EXPECT_EQ(tokens[1].type, TokenType::FLOAT3);
        EXPECT_EQ(tokens[2].type, TokenType::FLOAT4);
        EXPECT_EQ(tokens[3].type, TokenType::INT2);
        EXPECT_EQ(tokens[4].type, TokenType::INT3);
        EXPECT_EQ(tokens[5].type, TokenType::INT4);
        EXPECT_EQ(tokens[6].type, TokenType::UINT2);
        EXPECT_EQ(tokens[7].type, TokenType::UINT3);
        EXPECT_EQ(tokens[8].type, TokenType::UINT4);
    }
    
    // Matrix types
    {
        Lexer lexer("float2x2 float3x3 float4x4");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT2X2);
        EXPECT_EQ(tokens[1].type, TokenType::FLOAT3X3);
        EXPECT_EQ(tokens[2].type, TokenType::FLOAT4X4);
    }
    
    // float4 as identifier vs float and 4
    {
        Lexer lexer("float4 float 4");
        auto tokens = lexer.scanTokens();
        
        ASSERT_EQ(tokens.size(), 4);
        EXPECT_EQ(tokens[0].type, TokenType::FLOAT4);
        EXPECT_EQ(tokens[0].lexeme, "float4");
        EXPECT_EQ(tokens[1].type, TokenType::FLOAT);
        EXPECT_EQ(tokens[1].lexeme, "float");
        EXPECT_EQ(tokens[2].type, TokenType::INTEGER_LITERAL);
        EXPECT_EQ(tokens[2].lexeme, "4");
    }
}