#include <iostream>
#include "ast.hpp"
#include "CodeGen.h"
#include "parser_gen.hpp"

using namespace std;

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;
static std::map<std::string, llvm::Value *> NamedValues;

llvm::Value *IntegerAST::CodeGen(){
    return llvm::ConstantInt::get(TheContext,llvm::APInt( 64,uint64_t(value) ));
}
llvm::Value *DoubleAST::CodeGen(){
    return llvm::ConstantFP::get( TheContext,llvm::APFloat(value) );
}
llvm Value *VariableDeclarationAST::CodeGen(){
    return llvm::
}