#pragma once
#include <pch.h>

class ASTBase {
public:
	virtual ~ASTBase() {}
	virtual llvm::Value *codegen() = 0;
};

class Expression;
class FunctionDef;
class IDef;
llvm::Value *CompileError(const std::string &error);

class Block :ASTBase {
public:
	Block(llvm::Module &module,llvm::IRBuilder<> &builder);
	virtual ~Block();

	bool push_var(const std::string& name,Expression *expr = nullptr);
	bool push_const(const std::string& name, Expression *expr);

	enum class EXIST {
		variable,
		constant,
		other,//function
		none
	};

	virtual EXIST is_exist(const std::string &name);

	llvm::Module& get_module();
	llvm::IRBuilder<>& get_builder();
protected:
	std::unordered_map<std::string, llvm::Value *> *variables;
	std::unordered_map<std::string, llvm::Value *> *constants;
	llvm::Module &module;
	llvm::IRBuilder<> &builder;
};

class GlobalBlock :Block
{
public:
	GlobalBlock(llvm::Module &module, llvm::IRBuilder<> &builder);
	virtual ~GlobalBlock();
	bool push_func(const std::string& name, FunctionDef *expr = nullptr);
	virtual EXIST is_exist(const std::string &name)override;
protected:
	std::unordered_map<std::string, llvm::Value *> *functions;
};

namespace shared {
	Block *current_block = nullptr;
	GlobalBlock *global_block = nullptr;
};

class IDef {
public:
	virtual bool is_success() = 0;
	bool success;
};

class ConstantDef :ASTBase,IDef{
public:
	ConstantDef(const std::string &name, Expression *expr);
	virtual bool is_success() override;
	virtual llvm::Value *codegen()override;
};

class VariableDef :ASTBase, IDef {
public:
	VariableDef(const std::string &name, Expression *expr = nullptr);
	virtual bool is_success() override;
	virtual llvm::Value *codegen() = 0;
};

class Expression :ASTBase {
public:
	virtual llvm::Value *codegen() = 0;
};

//TODO:完成函数定义的AST定义
class FunctionDef :ASTBase,IDef {
public:
	virtual llvm::Value *codegen() = 0;
};

class FunctionCall :ASTBase {
public:
	virtual llvm::Value *codegen() = 0;
};


class BinaryExpr :Expression {
public:
	enum class Operator {
		_add = '+',
		_sub = '-',
		_mul = '*',
		_div = '/',
	};
	BinaryExpr(Operator op,Expression *left,Expression *right);
	virtual llvm::Value *codegen()override;
protected:
	Expression *left;
	Expression *right;
	Operator type;
};
using BinaryOperator = typename BinaryExpr::Operator;