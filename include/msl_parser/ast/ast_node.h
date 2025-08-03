#pragma once

#include <memory>
#include <string>

namespace msl_parser {
namespace ast {

class ASTVisitor;

struct SourceLocation {
    int line;
    int column;
    int offset;
    
    SourceLocation(int line = 0, int column = 0, int offset = 0)
        : line(line), column(column), offset(offset) {}
};

struct SourceRange {
    SourceLocation start;
    SourceLocation end;
    
    SourceRange() = default;
    SourceRange(const SourceLocation& start, const SourceLocation& end)
        : start(start), end(end) {}
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    
    virtual void accept(ASTVisitor* visitor) = 0;
    
    const SourceRange& getSourceRange() const { return sourceRange; }
    void setSourceRange(const SourceRange& range) { sourceRange = range; }
    
    ASTNode* getParent() const { return parent; }
    void setParent(ASTNode* p) { parent = p; }
    
protected:
    ASTNode() = default;
    ASTNode(const SourceRange& range) : sourceRange(range) {}
    
private:
    SourceRange sourceRange;
    ASTNode* parent = nullptr;
};

class Expression : public ASTNode {
public:
    Expression() = default;
    Expression(const SourceRange& range) : ASTNode(range) {}
};

class IntegerLiteral : public Expression {
public:
    explicit IntegerLiteral(int value) : value(value) {}
    IntegerLiteral(int value, const SourceRange& range) 
        : Expression(range), value(value) {}
    
    int getValue() const { return value; }
    
    void accept(ASTVisitor* visitor) override;
    
private:
    int value;
};

class FloatLiteral : public Expression {
public:
    explicit FloatLiteral(float value) : value(value) {}
    FloatLiteral(float value, const SourceRange& range)
        : Expression(range), value(value) {}
    
    float getValue() const { return value; }
    
    void accept(ASTVisitor* visitor) override;
    
private:
    float value;
};

class Identifier : public Expression {
public:
    explicit Identifier(const std::string& name) : name(name) {}
    Identifier(const std::string& name, const SourceRange& range)
        : Expression(range), name(name) {}
    
    const std::string& getName() const { return name; }
    
    void accept(ASTVisitor* visitor) override;
    
private:
    std::string name;
};

class UnaryExpression : public Expression {
public:
    enum class Operator {
        NEGATE,
        NOT,
        BITWISE_NOT
    };
    
    UnaryExpression(Operator op, std::unique_ptr<Expression> operand)
        : op(op), operand(std::move(operand)) {}
    
    Operator getOperator() const { return op; }
    Expression* getOperand() const { return operand.get(); }
    
    void accept(ASTVisitor* visitor) override;
    
private:
    Operator op;
    std::unique_ptr<Expression> operand;
};

class BinaryExpression : public Expression {
public:
    enum class Operator {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE
    };
    
    BinaryExpression(std::unique_ptr<Expression> left,
                    Operator op,
                    std::unique_ptr<Expression> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
    
    Expression* getLeft() const { return left.get(); }
    Expression* getRight() const { return right.get(); }
    Operator getOperator() const { return op; }
    
    void accept(ASTVisitor* visitor) override;
    
private:
    std::unique_ptr<Expression> left;
    Operator op;
    std::unique_ptr<Expression> right;
};

} // namespace ast
} // namespace msl_parser

#include "ast_visitor.h"

namespace msl_parser {
namespace ast {

inline void IntegerLiteral::accept(ASTVisitor* visitor) {
    visitor->visitIntegerLiteral(this);
}

inline void FloatLiteral::accept(ASTVisitor* visitor) {
    visitor->visitFloatLiteral(this);
}

inline void Identifier::accept(ASTVisitor* visitor) {
    visitor->visitIdentifier(this);
}

inline void UnaryExpression::accept(ASTVisitor* visitor) {
    visitor->visitUnaryExpression(this);
}

inline void BinaryExpression::accept(ASTVisitor* visitor) {
    visitor->visitBinaryExpression(this);
}

} // namespace ast
} // namespace msl_parser