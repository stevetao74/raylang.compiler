%{
	#include <pch.h>
	#include <ast/ast.h>
	namespace yy {
		using namespace ray::ast;
	};
	#include <parser/ray-parser.tab.h>
	typedef yy::parser::semantic_type YYSTYPE;
	typedef yy::parser::token::yytokentype tokens;
	extern int yylineno;
	void yyerror(const char *s);
	#define YYLTYPE yy::location

%}

%option noyywrap
%option yylineno
%option bison-locations

%%
"fn"					{return tokens::TOKEN_FUNCTION;}
"function"				{return tokens::TOKEN_FUNCTION;}
"var"					{return tokens::TOKEN_VAR;}
[a-zA-Z_][a-zA-Z_0-9]*	{return tokens::TOKEN_IDENTIFIER;}
"+"						{return tokens::TOKEN_PLUS;}
"-"						{return tokens::TOKEN_SUB;}
"*"						{return tokens::TOKEN_MUL;}
"/"						{return tokens::TOKEN_DIV;}
"%"						{return tokens::TOKEN_MOD;}
"("						{return tokens::TOKEN_LPAREN;}
")"						{return tokens::TOKEN_RPAREN;}
"{"						{return tokens::TOKEN_LBRACE;}
"}"						{return tokens::TOKEN_RBRACE;}
":"						{return tokens::TOKEN_COLON;}
%%

void yyerror(const char *s){
	std::cerr << s << std::endl;
}