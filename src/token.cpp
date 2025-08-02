#include "msl_parser/token.h"

namespace msl_parser {

const char* tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INTEGER_LITERAL: return "INTEGER_LITERAL";
        case TokenType::FLOAT_LITERAL: return "FLOAT_LITERAL";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::KERNEL: return "KERNEL";
        case TokenType::PLUS: return "PLUS";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        default: return "UNKNOWN";
    }
}

} // namespace msl_parser