%{
	#include <lexer/ray-lexer.flex.h>
	#include <pch.h>
	#include <ast/ast.h>
	extern int yylineno;
	extern void yyerror(const char *);
%}


%union{
	std::string *StrVal;
}
%start statement
%%

statement :
			expr ;
expr : ;
%%

void yy::parser::error(const std::string &msg){
	std::cerr << msg << std::endl;
}
