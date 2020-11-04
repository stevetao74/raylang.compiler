%{
	#include <lexer/ray-lexer.flex.h>
	#include <pch.h>
	#include <ast/ast.h>
	extern int yylineno;
	extern void yyerror(const char *);
	using namespace ray::ast;
%}

/// Token Definitions

%token <token>  TOKEN_FUNCTION
%token <token>  TOKEN_VAR
%token <token>  TOKEN_PLUS // +
%token <token>  TOKEN_SUB  // -
%token <token>  TOKEN_MUL  // *
%token <token>  TOKEN_DIV  // /
%token <token>  TOKEN_MOD  // %
%token <token>  TOKEN_LPAREN TOKEN_RPAREN TOKEN_LBRACE TOKEN_RBRACE  // ( ) { }
%token <StrVal>  TOKEN_IDENTIFIER  // IDENTIFIER
%type  expr
%type  function_def
%type  statement

//The yyval Definition
%union{
	std::string *StrVal;
}

//Start with statement
%start statement
%%

statement :
 function_def
|expr
;

function_def:
 TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAREN TOKEN_RPAREN {;}
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
