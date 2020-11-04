%{
	#include <lexer/ray-lexer.flex.h>
	#include <pch.h>
	#include <ast/ast.h>
	extern int yylineno;
	extern void yyerror(const char *);
%}

/// Token Definitions

%token <int> TOKEN_PLUS // +
%token <int> TOKEN_SUB  // -
%token <int> TOKEN_MUL  // *
%token <int> TOKEN_DIV  // /
%token <int> TOKEN_MOD  // %
%token <const char*> TOKEN_IDENTIFIER  // IDENTIFIER
%type  expr
%type  statement
//The yyval Definition
%union{
	std::string *StrVal;
}

//Start with statement
%start statement
%%

statement :
expr {;}
;


expr : 
TOKEN_IDENTIFIER      {printf("%s\n",yytext);}
| expr TOKEN_MUL  expr	{;}
| expr TOKEN_DIV  expr	{;}
| expr TOKEN_PLUS expr	{;}
| expr TOKEN_SUB  expr	{;}
;
%%

void yy::parser::error(const std::string &msg){
	std::cerr << msg << std::endl;
}
