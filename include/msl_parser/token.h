#ifndef MSL_PARSER_TOKEN_H
#define MSL_PARSER_TOKEN_H

#include <string>
#include <cstdint>

namespace msl_parser {

enum class TokenType {
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    IDENTIFIER,
    KERNEL,
    PLUS,
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