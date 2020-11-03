%{
	#include <pch.h>
	#include <parser/ray-parser.tab.h>
	typedef yy::parser::semantic_type YYSTYPE;

	extern int yylineno;
	extern char* yytext;

	void yyerror(const char *s);
%}

%option noyywrap
%option yylineno

%%
%%

void yyerror(const char *s){
	std::cerr << s << std::endl;
}