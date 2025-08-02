#ifndef MSL_PARSER_TOKEN_H
#define MSL_PARSER_TOKEN_H

#include <string>
#include <cstdint>

namespace msl_parser {

enum class TokenType {
    // Literals
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    
    // Identifier
    IDENTIFIER,
    
    // Keywords - Types
    VOID,
    BOOL,
    INT,
    UINT,
    SHORT,
    USHORT,
    CHAR,
    UCHAR,
    FLOAT,
    HALF,
    DOUBLE,
    
    // Keywords - Vector Types
    FLOAT2,
    FLOAT3,
    FLOAT4,
    INT2,
    INT3,
    INT4,
    UINT2,
    UINT3,
    UINT4,
    
    // Keywords - Matrix Types
    FLOAT2X2,
    FLOAT3X3,
    FLOAT4X4,
    
    // Keywords - Control Flow
    IF,
    ELSE,
    FOR,
    WHILE,
    DO,
    SWITCH,
    CASE,
    DEFAULT,
    BREAK,
    CONTINUE,
    RETURN,
    
    // Keywords - Metal-specific
    KERNEL,
    VERTEX,
    FRAGMENT,
    DEVICE,
    CONSTANT,
    THREAD,
    THREADGROUP,
    
    // Operators (placeholder for now)
    PLUS,
    
    // Special
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme;
    uint32_t line;
    uint32_t column;
    
    Token(TokenType type, const std::string& lexeme, uint32_t line, uint32_t column)
        : type(type), lexeme(lexeme), line(line), column(column) {}
};

const char* tokenTypeToString(TokenType type);

} // namespace msl_parser

#endif // MSL_PARSER_TOKEN_H