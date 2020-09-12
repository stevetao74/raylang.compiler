#include "AST.h"

namespace global
{
        void ASTTokenParser::SetTokenArray(std::vector<token> *array){
            tokens = *array;
            current_number = 0;
        }

        AST* ASTTokenParser::BaseParser(){
            token &tok = GetCurrent();
            switch (tok.type)
            {
            case TOKEN_CONST_FLOAT:
                return float_const_parser(tok);
                break;
            case TOKEN_CONST_INT:
                 return int_const_parser(tok);
                break;
            case TOKEN_STRING:
                return string_const_parser(tok);
                break;
            case TOKEN_ERROR:
            default:
                return NULL;
                break;
            }
        };
        AST* ASTTokenParser::float_const_parser(const token& tok){
            return new FloatAST(atof(tok.value.data()));
        }
        AST* ASTTokenParser::int_const_parser(const token& tok){
            return new IntAST(atoll(tok.value.data()));
        }
        AST* ASTTokenParser::string_const_parser(const token& tok){
            return new StringAST(tok.value.data());
        }
} // namespace global
