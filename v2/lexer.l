%{

#include <string>
#include "ast.hpp"
#include "parser_gen.hpp"

#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() { }

%}

%%

[\t\n]                  {}
[a-zA-Z_][a-zA-Z0-9_]*  {SAVE_TOKEN; return Identifier_t;}
[0-9]+.[0-9]*           {SAVE_TOKEN; return Double_t;}
[0-9]+                  {SAVE_TOKEN; return Integer_t;}
"="                     {return TOKEN(EQUAL);}
"=="                    {return TOKEN(CEQ);}
"!="                    {return TOKEN(CNE);}
"<"                     {return TOKEN(CLT);}
"<="                    {return TOKEN(CLE);}
">"                     {return TOKEN(CGT);}
">="                    {return TOKEN(CGE);}
"("                     {return TOKEN(LPAREN);}
")"                     {return TOKEN(RPAREN);}
"{"                     {return TOKEN(LBRACE);}
"}"                     {return TOKEN(RBRACE);}
"."                     {return TOKEN(DOT);}
","                     {return TOKEN(COMMA);}
"+"                     {return TOKEN(PLUS);}
"-"                     {return TOKEN(MINUS);}
"*"                     {return TOKEN(MUL);}
"/"                     {return TOKEN(DIV);}
.                       {printf("Unknown token %s!\n",yytext); yyterminate();}

%%