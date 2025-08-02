#include "msl_parser/token.h"

namespace msl_parser {

const char* tokenTypeToString(TokenType type) {
    switch (type) {
        // Literals
        case TokenType::INTEGER_LITERAL: return "INTEGER_LITERAL";
        case TokenType::FLOAT_LITERAL: return "FLOAT_LITERAL";
        
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
        
        // Operators
        case TokenType::PLUS: return "PLUS";
        
        // Special
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        
        default: return "UNKNOWN";
    }
}

} // namespace msl_parser