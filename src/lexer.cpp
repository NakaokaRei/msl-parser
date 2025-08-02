#include "msl_parser/lexer.h"
#include <cctype>
#include <unordered_map>

namespace msl_parser {

static const std::unordered_map<std::string, TokenType> keywords = {
    // Types
    {"void", TokenType::VOID},
    {"bool", TokenType::BOOL},
    {"int", TokenType::INT},
    {"uint", TokenType::UINT},
    {"short", TokenType::SHORT},
    {"ushort", TokenType::USHORT},
    {"char", TokenType::CHAR},
    {"uchar", TokenType::UCHAR},
    {"float", TokenType::FLOAT},
    {"half", TokenType::HALF},
    {"double", TokenType::DOUBLE},
    
    // Vector Types
    {"float2", TokenType::FLOAT2},
    {"float3", TokenType::FLOAT3},
    {"float4", TokenType::FLOAT4},
    {"int2", TokenType::INT2},
    {"int3", TokenType::INT3},
    {"int4", TokenType::INT4},
    {"uint2", TokenType::UINT2},
    {"uint3", TokenType::UINT3},
    {"uint4", TokenType::UINT4},
    
    // Matrix Types
    {"float2x2", TokenType::FLOAT2X2},
    {"float3x3", TokenType::FLOAT3X3},
    {"float4x4", TokenType::FLOAT4X4},
    
    // Control Flow
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"for", TokenType::FOR},
    {"while", TokenType::WHILE},
    {"do", TokenType::DO},
    {"switch", TokenType::SWITCH},
    {"case", TokenType::CASE},
    {"default", TokenType::DEFAULT},
    {"break", TokenType::BREAK},
    {"continue", TokenType::CONTINUE},
    {"return", TokenType::RETURN},
    
    // Metal-specific
    {"kernel", TokenType::KERNEL},
    {"vertex", TokenType::VERTEX},
    {"fragment", TokenType::FRAGMENT},
    {"device", TokenType::DEVICE},
    {"constant", TokenType::CONSTANT},
    {"thread", TokenType::THREAD},
    {"threadgroup", TokenType::THREADGROUP},
};

Lexer::Lexer(const std::string& source) : source(source) {}

std::vector<Token> Lexer::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    
    tokens.push_back(Token(TokenType::END_OF_FILE, "", line, column));
    return tokens;
}

void Lexer::scanToken() {
    char c = advance();
    
    if (isDigit(c)) {
        number();
    } else if (isAlpha(c)) {
        identifier();
    } else if (c == ' ' || c == '\r' || c == '\t') {
        // Ignore whitespace
    } else if (c == '\n') {
        line++;
        column = 1;
    } else {
        // Handle operators
        switch (c) {
            // Single-character operators
            case '+':
                if (peek() == '+') {
                    advance();
                    addToken(TokenType::PLUS_PLUS);
                } else if (peek() == '=') {
                    advance();
                    addToken(TokenType::PLUS_ASSIGN);
                } else {
                    addToken(TokenType::PLUS);
                }
                break;
            case '-':
                if (peek() == '-') {
                    advance();
                    addToken(TokenType::MINUS_MINUS);
                } else if (peek() == '=') {
                    advance();
                    addToken(TokenType::MINUS_ASSIGN);
                } else {
                    addToken(TokenType::MINUS);
                }
                break;
            case '*':
                if (peek() == '=') {
                    advance();
                    addToken(TokenType::MULTIPLY_ASSIGN);
                } else {
                    addToken(TokenType::MULTIPLY);
                }
                break;
            case '/':
                if (peek() == '=') {
                    advance();
                    addToken(TokenType::DIVIDE_ASSIGN);
                } else {
                    addToken(TokenType::DIVIDE);
                }
                break;
            case '%':
                if (peek() == '=') {
                    advance();
                    addToken(TokenType::MODULO_ASSIGN);
                } else {
                    addToken(TokenType::MODULO);
                }
                break;
            case '=':
                if (peek() == '=') {
                    advance();
                    addToken(TokenType::EQUAL);
                } else {
                    addToken(TokenType::ASSIGN);
                }
                break;
            case '!':
                if (peek() == '=') {
                    advance();
                    addToken(TokenType::NOT_EQUAL);
                } else {
                    addToken(TokenType::NOT);
                }
                break;
            case '<':
                if (peek() == '=') {
                    advance();
                    addToken(TokenType::LESS_EQUAL);
                } else if (peek() == '<') {
                    advance();
                    addToken(TokenType::LEFT_SHIFT);
                } else {
                    addToken(TokenType::LESS_THAN);
                }
                break;
            case '>':
                if (peek() == '=') {
                    advance();
                    addToken(TokenType::GREATER_EQUAL);
                } else if (peek() == '>') {
                    advance();
                    addToken(TokenType::RIGHT_SHIFT);
                } else {
                    addToken(TokenType::GREATER_THAN);
                }
                break;
            case '&':
                if (peek() == '&') {
                    advance();
                    addToken(TokenType::AND);
                } else {
                    addToken(TokenType::BITWISE_AND);
                }
                break;
            case '|':
                if (peek() == '|') {
                    advance();
                    addToken(TokenType::OR);
                } else {
                    addToken(TokenType::BITWISE_OR);
                }
                break;
            case '^':
                addToken(TokenType::BITWISE_XOR);
                break;
            case '~':
                addToken(TokenType::BITWISE_NOT);
                break;
            case '?':
                addToken(TokenType::QUESTION);
                break;
            case ':':
                addToken(TokenType::COLON);
                break;
            default:
                // Skip unknown characters for now
                break;
        }
    }
}

void Lexer::number() {
    // Check for hex or binary prefix
    if (peek() == 'x' || peek() == 'X') {
        // Hexadecimal
        advance(); // consume 'x' or 'X'
        while (isHexDigit(peek())) {
            advance();
        }
        addToken(TokenType::INTEGER_LITERAL);
        return;
    } else if (peek() == 'b' || peek() == 'B') {
        // Binary
        advance(); // consume 'b' or 'B'
        while (peek() == '0' || peek() == '1') {
            advance();
        }
        addToken(TokenType::INTEGER_LITERAL);
        return;
    }
    
    // Decimal integer part
    while (isDigit(peek())) {
        advance();
    }
    
    // Look for a fractional part
    if (peek() == '.') {
        // Check if there's a digit after the dot or if it's just a trailing dot
        if (isDigit(peekNext())) {
            // Consume the "."
            advance();
            
            while (isDigit(peek())) {
                advance();
            }
        } else {
            // Just a trailing dot like "10."
            advance();
        }
    }
    
    // Look for exponent
    if (peek() == 'e' || peek() == 'E') {
        advance();
        if (peek() == '+' || peek() == '-') {
            advance();
        }
        while (isDigit(peek())) {
            advance();
        }
    }
    
    // Check for float suffix
    if (peek() == 'f' || peek() == 'F' || peek() == 'h' || peek() == 'H') {
        advance();
        addToken(TokenType::FLOAT_LITERAL);
        return;
    }
    
    // Determine if it's float or integer
    std::string text = source.substr(start, current - start);
    if (text.find('.') != std::string::npos || 
        text.find('e') != std::string::npos || 
        text.find('E') != std::string::npos) {
        addToken(TokenType::FLOAT_LITERAL);
    } else {
        addToken(TokenType::INTEGER_LITERAL);
    }
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::isHexDigit(char c) {
    return (c >= '0' && c <= '9') || 
           (c >= 'a' && c <= 'f') || 
           (c >= 'A' && c <= 'F');
}

bool Lexer::isAtEnd() {
    return current >= source.length();
}

char Lexer::advance() {
    column++;
    return source[current++];
}

char Lexer::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Lexer::peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

void Lexer::addToken(TokenType type) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, line, column - text.length()));
}

void Lexer::identifier() {
    while (isAlphaNumeric(peek())) {
        advance();
    }
    
    std::string text = source.substr(start, current - start);
    
    // Check if it's a keyword
    auto it = keywords.find(text);
    TokenType type = (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;
    
    addToken(type);
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Lexer::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

} // namespace msl_parser