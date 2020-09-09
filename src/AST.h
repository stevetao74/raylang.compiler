#include <vector>
#include <string>


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
    public virtual ~AST() = 0;
};

class VariableAST extends AST{
    
    public VariableAST(const std::string &name,const VariableType &type):name(name),type(type){}
    
    public virtual ~VariableAST()override{}
    
    protected VariableType type;
    
    protected std::string name;
};

class IntAST extends AST{
    
    public IntAST(const int64_t &value):value(value){}
    public virtual ~IntAST()override{}
    
    protected int64_t value;
};

class BinaryAST extends AST{
    
    public BinaryAST(const std::string &op,AST *lhs,AST *rhs): bin_operator(op) ,lhs(lhs) ,rhs(rhs){

    }
    public virtual ~BinaryAST()override{}

    protected std::string bin_operator;
    protected AST *lhs,*rhs;

};
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

#undef abstract
#undef extends
#undef class
#undef protected 
#undef private
#undef public