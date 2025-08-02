#include <iostream>
#include "msl_parser/lexer.h"
#include "msl_parser/token.h"

int main() {
    std::string source = "42";
    msl_parser::Lexer lexer(source);
    auto tokens = lexer.scanTokens();
    
    for (const auto& token : tokens) {
        std::cout << msl_parser::tokenTypeToString(token.type) 
                  << ": " << token.lexeme << std::endl;
    }
    
    return 0;
}