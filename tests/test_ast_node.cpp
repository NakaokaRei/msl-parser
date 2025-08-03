#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "msl_parser/ast/ast_node.h"
#include "msl_parser/ast/ast_visitor.h"

using namespace msl_parser::ast;

TEST(ASTNodeTest, CreateIntegerLiteral) {
    // Test that we can create an integer literal node
    auto node = std::make_unique<IntegerLiteral>(42);
    
    EXPECT_EQ(node->getValue(), 42);
}

TEST(ASTNodeTest, SourceLocationTracking) {
    // Test that nodes can track their source location
    SourceLocation start(1, 5, 4);
    SourceLocation end(1, 7, 6);
    SourceRange range(start, end);
    
    auto node = std::make_unique<IntegerLiteral>(42, range);
    
    EXPECT_EQ(node->getSourceRange().start.line, 1);
    EXPECT_EQ(node->getSourceRange().start.column, 5);
    EXPECT_EQ(node->getSourceRange().start.offset, 4);
    EXPECT_EQ(node->getSourceRange().end.line, 1);
    EXPECT_EQ(node->getSourceRange().end.column, 7);
    EXPECT_EQ(node->getSourceRange().end.offset, 6);
}

TEST(ASTNodeTest, ParentChildRelationship) {
    // Test that parent-child relationships work
    auto parent = std::make_unique<BinaryExpression>(
        std::make_unique<IntegerLiteral>(1),
        BinaryExpression::Operator::ADD,
        std::make_unique<IntegerLiteral>(2)
    );
    
    auto left = parent->getLeft();
    auto right = parent->getRight();
    
    // Set parent relationships
    left->setParent(parent.get());
    right->setParent(parent.get());
    
    EXPECT_EQ(left->getParent(), parent.get());
    EXPECT_EQ(right->getParent(), parent.get());
}

// Visitor pattern tests
class TestVisitor : public ASTVisitor {
public:
    int integerLiteralCount = 0;
    int floatLiteralCount = 0;
    int identifierCount = 0;
    int unaryExpressionCount = 0;
    int binaryExpressionCount = 0;
    std::vector<int> visitedValues;
    std::vector<float> visitedFloats;
    std::vector<std::string> visitedIdentifiers;
    
    void visitIntegerLiteral(IntegerLiteral* node) override {
        integerLiteralCount++;
        visitedValues.push_back(node->getValue());
    }
    
    void visitFloatLiteral(FloatLiteral* node) override {
        floatLiteralCount++;
        visitedFloats.push_back(node->getValue());
    }
    
    void visitIdentifier(Identifier* node) override {
        identifierCount++;
        visitedIdentifiers.push_back(node->getName());
    }
    
    void visitUnaryExpression(UnaryExpression* node) override {
        unaryExpressionCount++;
        // Visit operand
        node->getOperand()->accept(this);
    }
    
    void visitBinaryExpression(BinaryExpression* node) override {
        binaryExpressionCount++;
        // Visit children
        node->getLeft()->accept(this);
        node->getRight()->accept(this);
    }
};

TEST(ASTVisitorTest, VisitIntegerLiteral) {
    // Test that visitor can visit integer literals
    auto node = std::make_unique<IntegerLiteral>(42);
    TestVisitor visitor;
    
    node->accept(&visitor);
    
    EXPECT_EQ(visitor.integerLiteralCount, 1);
    EXPECT_EQ(visitor.visitedValues.size(), 1);
    EXPECT_EQ(visitor.visitedValues[0], 42);
}

TEST(ASTVisitorTest, VisitBinaryExpression) {
    // Test that visitor can traverse binary expressions
    auto expr = std::make_unique<BinaryExpression>(
        std::make_unique<IntegerLiteral>(10),
        BinaryExpression::Operator::ADD,
        std::make_unique<IntegerLiteral>(20)
    );
    
    TestVisitor visitor;
    expr->accept(&visitor);
    
    EXPECT_EQ(visitor.binaryExpressionCount, 1);
    EXPECT_EQ(visitor.integerLiteralCount, 2);
    EXPECT_EQ(visitor.visitedValues.size(), 2);
    EXPECT_EQ(visitor.visitedValues[0], 10);
    EXPECT_EQ(visitor.visitedValues[1], 20);
}

TEST(ASTNodeTest, CreateFloatLiteral) {
    // Test float literal creation
    auto node = std::make_unique<FloatLiteral>(3.14f);
    EXPECT_FLOAT_EQ(node->getValue(), 3.14f);
}

TEST(ASTNodeTest, CreateIdentifier) {
    // Test identifier creation
    auto node = std::make_unique<Identifier>("myVariable");
    EXPECT_EQ(node->getName(), "myVariable");
}

TEST(ASTNodeTest, CreateUnaryExpression) {
    // Test unary expression creation
    auto operand = std::make_unique<IntegerLiteral>(42);
    auto unary = std::make_unique<UnaryExpression>(
        UnaryExpression::Operator::NEGATE,
        std::move(operand)
    );
    
    EXPECT_EQ(unary->getOperator(), UnaryExpression::Operator::NEGATE);
    EXPECT_NE(unary->getOperand(), nullptr);
}