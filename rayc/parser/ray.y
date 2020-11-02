%{
	#include <pch.h>
	#include <ast/ast.h>
	extern int yylineno;
%}


%union{
	std::string *StrVal;
}
%start statement
%%

statement : ;

%%
