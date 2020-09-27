#include <vector>
#include <string>
#include <cstring>
#include <llvm/IR/Value.h>
#include <llvm/IR/Argument.h>

//{
#define abstract
#define extends :
#define class struct
#define protected protected:
#define private private:
#define public public:
//}

//{
class StatementAST;
class ExpressionAST;
class VariableDeclarationAST;
using StatementList = std::vector<StatementAST *>;
using ExpressionList = std::vector<ExpressionAST *>;
using VariableList = std::vector<VariableDeclarationAST *>;

abstract class ASTBase
{
public
    virtual ~ASTBase(){};
public
    virtual llvm::Value *CodeGen() { return nullptr; };
};

class ExpressionAST extends ASTBase
{
};

class StatementAST extends ASTBase
{
};

class IntegerAST extends ExpressionAST
{
public
    int32_t value;
public
    IntegerAST(int32_t value) : value(value) {}
public
    virtual llvm::Value *CodeGen();
};

class DoubleAST extends ExpressionAST
{
public
    double value;
    DoubleAST(double value) : value(value) {}
public
    virtual llvm::Value *CodeGen();
};

class IdentifierAST : ExpressionAST
{
public
    std::string name;
    IdentifierAST(const std::string &name) : name(name) {}
    virtual llvm::Value *CodeGen();
};
class MethodCallAST extends ExpressionAST
{
public
    const IdentifierAST &id;
    ExpressionList arguments;
    MethodCallAST(const IdentifierAST &id, ExpressionList &arguments) : id(id), arguments(arguments) {}
    MethodCallAST(const IdentifierAST &id) : id(id) {}
    virtual llvm::Value *CodeGen();
};

class BinaryOperatorAST extends ExpressionAST
{
public
    int op;
    ExpressionAST &lhs;
    ExpressionAST &rhs;
    BinaryOperatorAST(ExpressionAST &lhs, int op, ExpressionAST &rhs) : lhs(lhs), rhs(rhs), op(op) {}
    virtual llvm::Value *CodeGen();
};

class AssignmentAST extends ExpressionAST
{
public
    IdentifierAST &lhs;
    ExpressionAST &rhs;
    AssignmentAST(IdentifierAST &lhs, ExpressionAST &rhs) : lhs(lhs), rhs(rhs) {}
    virtual llvm::Value *CodeGen();
};

class BlockAST extends ExpressionAST
{
public
    StatementList statements;
    BlockAST() {}
    virtual llvm::Value *CodeGen();
};

class ExpressionASTStatement extends StatementAST
{
public
    ExpressionAST &expression;
    ExpressionASTStatement(ExpressionAST &expression) : expression(expression) {}
    virtual llvm::Value *CodeGen();
};

class VariableDeclarationAST extends StatementAST
{
public
    const IdentifierAST &type;
    IdentifierAST &id;
    ExpressionAST *assignmentExpr;
    VariableDeclarationAST(const IdentifierAST &type, IdentifierAST &id) : type(type), id(id) {}
    VariableDeclarationAST(const IdentifierAST &type, IdentifierAST &id, ExpressionAST *assignmentExpr) : type(type), id(id), assignmentExpr(assignmentExpr) {}
    virtual llvm::Value *CodeGen();
};

class FunctionDeclarationAST extends StatementAST
{
public
    const IdentifierAST &type;
    const IdentifierAST &id;
    VariableList arguments;
    BlockAST &block;
    FunctionDeclarationAST(const IdentifierAST &type, const IdentifierAST &id,
                           const VariableList &arguments, BlockAST &block) : type(type), id(id), arguments(arguments), block(block) {}
    virtual llvm::Value *CodeGen();
};
//}

//{
#undef abstract
#undef extends
#undef class
#undef protected
#undef private
#undef public
//}