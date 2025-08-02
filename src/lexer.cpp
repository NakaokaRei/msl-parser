#include "msl_parser/lexer.h"
#include <cctype>

namespace msl_parser {

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
    } else if (c == ' ' || c == '\r' || c == '\t') {
        // Ignore whitespace
    } else if (c == '\n') {
        line++;
        column = 1;
    } else {
        // Skip unknown characters for now
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

} // namespace msl_parser