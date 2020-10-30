#include <pch.h>
#include <ast/ast.h>

Block::Block(llvm::Module & module, llvm::IRBuilder<>& builder)
	:module(module),builder(builder)
{
	variables = new std::unordered_map<std::string, llvm::Value *>;
	constants = new std::unordered_map<std::string, llvm::Value *>;
}

Block::~Block()
{
	delete variables;
	delete constants;
}

bool Block::push_var(const std::string & name, Expression *expr)
{
	if (is_exist(name) == EXIST::none) {
		auto value = (expr ==nullptr) ? nullptr : expr->codegen();
		if (nullptr != value) {
			variables->insert(std::make_pair(name, value));
			return true;
		}
	}
	return false;
}

bool Block::push_const(const std::string & name, Expression *expr)
{
	if (is_exist(name) == EXIST::none) {
		auto value = expr->codegen();
		if (value != nullptr) {
			constants->insert(std::make_pair(name, value));
			return true;
		}
	}
	return false;
}

Block::EXIST Block::is_exist(const std::string & name)
{
	if (variables->count(name) != 0) {
		return EXIST::variable;
	}
	else if (constants->count(name) != 0) {
		return EXIST::constant;
	}
	else
	{
		return EXIST::none;
	}
}

llvm::Module & Block::get_module()
{
	return module;
}

llvm::IRBuilder<>& Block::get_builder()
{
	return builder;
}

GlobalBlock::GlobalBlock(llvm::Module & module, llvm::IRBuilder<>& builder):Block(module,builder)
{
	functions = new std::unordered_map<std::string, llvm::Value *>;
}

GlobalBlock::~GlobalBlock()
{
	delete functions;
}

bool GlobalBlock::push_func(const std::string & name, FunctionDef * expr)
{
	if (is_exist(name) == EXIST::none) {
		auto value = expr->codegen();
		if (value != nullptr) {
			functions->insert(std::make_pair(name, expr->codegen()));
			return true;
		}
	}
	return false;
}

GlobalBlock::EXIST GlobalBlock::is_exist(const std::string & name)
{
	if (functions->count(name) != 0) {
		return EXIST::other;
	}
	else
	{
		return Block::is_exist(name);
	}
}

ConstantDef::ConstantDef(const std::string & name, Expression * expr)
{
	success = shared::current_block->push_const(name, expr);
}

bool ConstantDef::is_success()
{
	return this->success;
}

llvm::Value * ConstantDef::codegen()
{
	return nullptr;
}

VariableDef::VariableDef(const std::string & name, Expression * expr)
{
	success = shared::current_block->push_var(name, expr);
}

bool VariableDef::is_success()
{
	return this->success;
}

BinaryExpr::BinaryExpr(Operator op, Expression * left, Expression * right)
:type(op),left(left),right(right)
{

}

llvm::Value * BinaryExpr::codegen()
{
	auto &builder = shared::current_block->get_builder();
	auto lv = left->codegen();
	auto rv = right->codegen();
	switch (type)
	{
	case BinaryExpr::Operator::_add:
		builder.CreateAdd(lv, rv);
		break;
	case BinaryExpr::Operator::_sub:
		builder.CreateSub(lv, rv);
		break;
	case BinaryExpr::Operator::_mul:
		builder.CreateMul(lv, rv);
		break;
	case BinaryExpr::Operator::_div:
		builder.CreateSDiv(lv, rv);
		break;
	default:
		break;
	}
	return nullptr;
}

llvm::Value * CompileError(const std::string & error)
{
	
	std::cerr << error << std::endl;
	return nullptr;
}
