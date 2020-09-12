#include <vector>
#include <string>
#include <cstring>
#include "token.h"

#define abstract
#define extends :
#define class struct
#define protected protected:
#define private private:
#define public public:

enum class VariableType{
    Int,
    Double,
    String,
    Pointer
};

abstract class AST{
    public virtual ~AST() = 0; //Make it abstract
};

class VariableAST extends AST{
    
    public VariableAST(const std::string &name,const VariableType &type):name(name),type(type){}
    
    public virtual ~VariableAST()override{}
    
    protected VariableType type;
    
    protected std::string name;
};

//===========constants==================
class IntAST extends AST{
    
    public IntAST(const int64_t &value):value(value){}
    public virtual ~IntAST()override{}
    
    protected int64_t value;
};

class FloatAST extends AST{
    public FloatAST(const double &value):value(value){}
    public virtual ~FloatAST()override{}

    protected double value;
};


class StringAST extends AST{
    public StringAST(const std::string &value):value(value){}
    public virtual ~StringAST()override{}

    protected std::string value;
};

class PointerAST extends AST{
    public PointerAST(intptr_t* &value):value(value){}
    public virtual ~PointerAST()override{}

    protected intptr_t *value;
};

//================expressions
class BinaryAST extends AST{
    
    public BinaryAST(const std::string &op,AST *lhs,AST *rhs): bin_operator(op) ,lhs(lhs) ,rhs(rhs){

    }
    public virtual ~BinaryAST()override{}

    protected std::string bin_operator;
    protected AST *lhs,*rhs;

};

//For Fuction Defines
struct Argument{
    VariableType type;
    std::string name;
};
class FunctionDefineAST extends AST{

    public FunctionDefineAST(const VariableType &type,const std::string &name,AST *body,const std::vector<Argument> &arguments)
        :type(type),name(name),body(body),arguments(arguments){}
    public virtual ~FunctionDefineAST()override{}

    protected VariableType type;
    protected std::string name;
    protected AST *body;
    protected std::vector<Argument> arguments;
};

class FunctionCallAST extends AST{
    public FunctionCallAST(const std::string &name,const std::vector<AST*> &arguments):name(name),arguments(arguments){}
    public ~FunctionCallAST(){}

    protected std::string name;
    protected std::vector<AST*> arguments;

};


//the core of ASTParser
namespace global
{
    class ASTTokenParser{
        protected static std::vector<token> tokens;
        private static size_t current_number;

        public static void SetTokenArray(std::vector<token>*);

        public inline static void NextToken(){
            current_number++;
        }

        public inline static token &GetCurrent(){
            return tokens[current_number];
        }

        public static AST* BaseParser();
        public static AST* float_const_parser(const token&);
        public static AST* int_const_parser(const token&);
        public static AST* string_const_parser(const token&);
    }TokenParser;
}; // namespace global


#undef abstract
#undef extends
#undef class
#undef protected 
#undef private
#undef public