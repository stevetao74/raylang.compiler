#include <iostream>
#include "ast.hpp"
#include "CodeGen.h"
#include "parser_gen.hpp"

using namespace std;

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;
static std::map<std::string, llvm::AllocaInst*> NamedValues;
/// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.  This is used for mutable variables etc.
static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction,
                                          const std::string &VarName) {
  llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                 TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(llvm::Type::getDoubleTy(TheContext), 0,
                           VarName.c_str());
}

llvm::Value *IntegerAST::CodeGen(){
    return llvm::ConstantInt::get(TheContext,llvm::APInt( 64,uint64_t(value) ));
}
llvm::Value *DoubleAST::CodeGen(){
    return llvm::ConstantFP::get( TheContext,llvm::APFloat(value) );
}
llvm::Value *VariableDeclarationAST::CodeGen(){
    llvm::Value *V = NamedValues[this->id.name];
    if(!V){
        
    }
}