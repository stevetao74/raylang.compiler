%{
	#include <lexer/ray-lexer.flex.h>
	#include <pch.h>
	#include <ast/ast.h>
	extern int yylineno;
	extern void yyerror(const char *);
	namespace yy {
		using namespace ray::ast;
	};
%}
//This is used for error handling.
%locations
/// Token Definitions

%token <token>  TOKEN_FUNCTION
%token <token>  TOKEN_VAR   //keyword 'var'
%token <token>  TOKEN_PLUS  // +
%token <token>  TOKEN_SUB   // -
%token <token>  TOKEN_MUL   // *
%token <token>  TOKEN_DIV   // /
%token <token>  TOKEN_MOD   // %
%token <token>  TOKEN_COLON // :
%token <token>  TOKEN_LPAREN TOKEN_RPAREN TOKEN_LBRACE TOKEN_RBRACE  // ( ) { }
%token <StrVal>  TOKEN_IDENTIFIER  // IDENTIFIER
%type  expr
%type  function_def
%type  var_def
%type  statement
//The yyval Definition
%union{
	std::string *StrVal;
	yy::ExpressionBase *expr;
}

//Start with statement
%start statement
%%

statement :
  function_def
| var_def
;

function_def :
 TOKEN_FUNCTION TOKEN_IDENTIFIER TOKEN_LPAREN TOKEN_RPAREN {;}
;

expr : 
  expr TOKEN_MUL  expr	{;}
| expr TOKEN_DIV  expr	{;}
| expr TOKEN_PLUS expr	{;}
| expr TOKEN_SUB  expr	{;}
| TOKEN_IDENTIFIER      {printf("%s\n",yytext);}
;

var_def :
  TOKEN_VAR TOKEN_IDENTIFIER {;}
;

%%

void yy::parser::error(const location_type& loc,const std::string &msg){
	std::cerr << msg << std::endl;
}
