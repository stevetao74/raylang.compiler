%option noyywrap
%option yylineno
%{
	#include <pch.h>

	extern int yylineno;
	extern char* yytext;

	int yyerror(const char *s);
%}


%%
%%

int yyerror(const char *s){
	fprintf(stderr,"%s",s);
}