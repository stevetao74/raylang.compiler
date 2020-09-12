#include "FlexLexer.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "token.h"
#include "AST.h"

std::vector<token> global::ASTTokenParser::tokens = {};
size_t global::ASTTokenParser::current_number = 0;


namespace
{
    class Application
    {
    public:
        Application();
        ~Application();
        int main(int argc, char *argv[]);
    protected:
        std::vector<token> *token_list;
    };
} // namespace


int main(int argc, char *argv[])
{
    Application app;
    return app.main(argc,argv);
}

namespace
{
    int Application::main(int argc, char *argv[])
    {
        std::stringstream out_stream;
        yyFlexLexer *lexer = new yyFlexLexer(std::cin, out_stream);
        while (lexer->yylex() != TOKEN_EOF)
        {
            token_list->push_back(getToken());
        }
        global::TokenParser.SetTokenArray(token_list);
        return 0;
    }
    Application::Application(){
        this->token_list = new  std::vector<token>;
    }

    Application::~Application(){
        delete this->token_list;
    }

} // namespace
