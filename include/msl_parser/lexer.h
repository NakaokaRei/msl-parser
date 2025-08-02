#ifndef MSL_PARSER_LEXER_H
#define MSL_PARSER_LEXER_H

#include <string>
#include <vector>
#include "msl_parser/token.h"

namespace msl_parser {

class Lexer {
public:
    explicit Lexer(const std::string& source);
    std::vector<Token> scanTokens();

private:
    std::string source;
    std::vector<Token> tokens;
    size_t start = 0;
    size_t current = 0;
    uint32_t line = 1;
    uint32_t column = 1;
};

} // namespace msl_parser

#endif // MSL_PARSER_LEXER_H