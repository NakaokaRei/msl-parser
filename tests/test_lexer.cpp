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
        
        // Let's debug by printing the actual token count
        // for (size_t i = 0; i < tokens.size(); i++) {
        //     std::cout << i << ": " << tokenTypeToString(tokens[i].type) << " " << tokens[i].lexeme << std::endl;
        // }
        
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