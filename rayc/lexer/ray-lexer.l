%{
	#include <pch.h>
	#include <parser/ray-parser.tab.h>
	typedef yy::parser::semantic_type YYSTYPE;
	typedef yy::parser::token::yytokentype tokens;
	extern int yylineno;
	void yyerror(const char *s);
%}

%option noyywrap
%option yylineno

%%
[a-zA-Z_][a-zA-Z_0-9]*	{return tokens::TOKEN_IDENTIFIER;}
"+"						{return tokens::TOKEN_PLUS;}
"-"						{return tokens::TOKEN_SUB;}
"*"						{return tokens::TOKEN_MUL;}
"/"						{return tokens::TOKEN_DIV;}
"%"						{return tokens::TOKEN_MOD;}
%%

void yyerror(const char *s){
	std::cerr << s << std::endl;
}