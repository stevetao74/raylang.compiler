#include <stack>
#include <map>
#include <string>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
// using  llvm::BasicBlock;
// using  llvm::Value;
// using llvm::Function;
// class BlockAST;

// class CodeGenBlock {
// public:
//     llvm::BasicBlock *block;
//     std::map<std::string, Value*> locals;
// };

// class CodeGenContext {
//     std::stack<CodeGenBlock *> blocks;
//     llvm::Function *mainFunction;

// public:
//     llvm::Module *module;
//     CodeGenContext() { module = new Module("main", getGlobalContext()); }
    
//     void generateCode(BlockAST& root);
//     GenericValue runCode();
//     std::map<std::string, Value*>& locals() { return blocks.top()->locals; }
//     BasicBlock *currentBlock() { return blocks.top()->block; }
//     void pushBlock(BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->block = block; }
//     void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
// };