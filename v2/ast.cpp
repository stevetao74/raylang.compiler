#include "ast.hpp"
#include <iostream>
using namespace llvm;
Value* BlockAST::CodeGen(CodeGenContext& context)
{
    StatementList::const_iterator it;
    Value *last = NULL;
    for (it = statements.begin(); it != statements.end(); it++) {
        std::cout << "Generating code for " << typeid(**it).name() << std::endl;
        last = (**it).CodeGen(context);
    }
    std::cout << "Creating block" << std::endl;
    return last;
}