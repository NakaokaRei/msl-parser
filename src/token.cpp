#include "msl_parser/token.h"

namespace msl_parser {

const char* tokenTypeToString(TokenType type) {
    switch (type) {
        // Literals
        case TokenType::INTEGER_LITERAL: return "INTEGER_LITERAL";
        case TokenType::FLOAT_LITERAL: return "FLOAT_LITERAL";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        
        // Identifier
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        
        // Keywords - Types
        case TokenType::VOID: return "VOID";
        case TokenType::BOOL: return "BOOL";
        case TokenType::INT: return "INT";
        case TokenType::UINT: return "UINT";
        case TokenType::SHORT: return "SHORT";
        case TokenType::USHORT: return "USHORT";
        case TokenType::CHAR: return "CHAR";
        case TokenType::UCHAR: return "UCHAR";
        case TokenType::FLOAT: return "FLOAT";
        case TokenType::HALF: return "HALF";
        case TokenType::DOUBLE: return "DOUBLE";
        
        // Keywords - Vector Types
        case TokenType::FLOAT2: return "FLOAT2";
        case TokenType::FLOAT3: return "FLOAT3";
        case TokenType::FLOAT4: return "FLOAT4";
        case TokenType::INT2: return "INT2";
        case TokenType::INT3: return "INT3";
        case TokenType::INT4: return "INT4";
        case TokenType::UINT2: return "UINT2";
        case TokenType::UINT3: return "UINT3";
        case TokenType::UINT4: return "UINT4";
        
        // Keywords - Matrix Types
        case TokenType::FLOAT2X2: return "FLOAT2X2";
        case TokenType::FLOAT3X3: return "FLOAT3X3";
        case TokenType::FLOAT4X4: return "FLOAT4X4";
        
        // Keywords - Control Flow
        case TokenType::IF: return "IF";
        case TokenType::ELSE: return "ELSE";
        case TokenType::FOR: return "FOR";
        case TokenType::WHILE: return "WHILE";
        case TokenType::DO: return "DO";
        case TokenType::SWITCH: return "SWITCH";
        case TokenType::CASE: return "CASE";
        case TokenType::DEFAULT: return "DEFAULT";
        case TokenType::BREAK: return "BREAK";
        case TokenType::CONTINUE: return "CONTINUE";
        case TokenType::RETURN: return "RETURN";
        
        // Keywords - Metal-specific
        case TokenType::KERNEL: return "KERNEL";
        case TokenType::VERTEX: return "VERTEX";
        case TokenType::FRAGMENT: return "FRAGMENT";
        case TokenType::DEVICE: return "DEVICE";
        case TokenType::CONSTANT: return "CONSTANT";
        case TokenType::THREAD: return "THREAD";
        case TokenType::THREADGROUP: return "THREADGROUP";
        
        // Operators - Arithmetic
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::DIVIDE: return "DIVIDE";
        case TokenType::MODULO: return "MODULO";
        
        // Operators - Assignment
        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::PLUS_ASSIGN: return "PLUS_ASSIGN";
        case TokenType::MINUS_ASSIGN: return "MINUS_ASSIGN";
        case TokenType::MULTIPLY_ASSIGN: return "MULTIPLY_ASSIGN";
        case TokenType::DIVIDE_ASSIGN: return "DIVIDE_ASSIGN";
        case TokenType::MODULO_ASSIGN: return "MODULO_ASSIGN";
        
        // Operators - Comparison
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";
        case TokenType::LESS_THAN: return "LESS_THAN";
        case TokenType::GREATER_THAN: return "GREATER_THAN";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        
        // Operators - Logical
        case TokenType::AND: return "AND";
        case TokenType::OR: return "OR";
        case TokenType::NOT: return "NOT";
        
        // Operators - Bitwise
        case TokenType::BITWISE_AND: return "BITWISE_AND";
        case TokenType::BITWISE_OR: return "BITWISE_OR";
        case TokenType::BITWISE_XOR: return "BITWISE_XOR";
        case TokenType::BITWISE_NOT: return "BITWISE_NOT";
        case TokenType::LEFT_SHIFT: return "LEFT_SHIFT";
        case TokenType::RIGHT_SHIFT: return "RIGHT_SHIFT";
        
        // Operators - Other
        case TokenType::PLUS_PLUS: return "PLUS_PLUS";
        case TokenType::MINUS_MINUS: return "MINUS_MINUS";
        case TokenType::QUESTION: return "QUESTION";
        case TokenType::COLON: return "COLON";
        
        // Delimiters
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
        
        // Punctuation
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::ARROW: return "ARROW";
        case TokenType::SCOPE_RESOLUTION: return "SCOPE_RESOLUTION";
        
        // Attributes
        case TokenType::ATTRIBUTE_LEFT: return "ATTRIBUTE_LEFT";
        case TokenType::ATTRIBUTE_RIGHT: return "ATTRIBUTE_RIGHT";
        
        // Special
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        
        default: return "UNKNOWN";
    }
}

} // namespace msl_parser