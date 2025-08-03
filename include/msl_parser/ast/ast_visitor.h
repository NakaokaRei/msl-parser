#pragma once

namespace msl_parser {
namespace ast {

class IntegerLiteral;
class FloatLiteral;
class Identifier;
class UnaryExpression;
class BinaryExpression;

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;
    
    virtual void visitIntegerLiteral(IntegerLiteral* node) = 0;
    virtual void visitFloatLiteral(FloatLiteral* node) = 0;
    virtual void visitIdentifier(Identifier* node) = 0;
    virtual void visitUnaryExpression(UnaryExpression* node) = 0;
    virtual void visitBinaryExpression(BinaryExpression* node) = 0;
};

} // namespace ast
} // namespace msl_parser