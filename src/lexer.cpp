#include "msl_parser/lexer.h"

namespace msl_parser {

Lexer::Lexer(const std::string& source) : source(source) {}

std::vector<Token> Lexer::scanTokens() {
    while (current < source.length()) {
        start = current;
        
        char c = source[current];
        if (c >= '0' && c <= '9') {
            // Simple integer literal scanning
            while (current < source.length() && source[current] >= '0' && source[current] <= '9') {
                current++;
            }
            std::string lexeme = source.substr(start, current - start);
            tokens.push_back(Token(TokenType::INTEGER_LITERAL, lexeme, line, column));
            column += current - start;
        } else {
            // Skip unknown characters for now
            current++;
            column++;
        }
    }
    
    tokens.push_back(Token(TokenType::END_OF_FILE, "", line, column));
    return tokens;
}

} // namespace msl_parser