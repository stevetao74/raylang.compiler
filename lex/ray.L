%{
    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <string>
    #include "token.h"
    token now;
%}

%x COMMENT
%x STRING
%x SINGLE_STRING

%%

"function"              {now.type=TOKEN_KEYWORD_FUNC;  return TOKEN_KEYWORD_FUNC;}
"fn"                    {now.type=TOKEN_KEYWORD_FUNC;  return TOKEN_KEYWORD_FUNC;}
"as"                    {now.type=TOKEN_KEYWORD_AS;    return TOKEN_KEYWORD_AS;}
"get"                   {now.type=TOKEN_KEYWORD_GET;   return TOKEN_KEYWORD_GET;}
"put"                   {now.type=TOKEN_KEYWORD_PUT;   return TOKEN_KEYWORD_PUT;}
"if"                    {now.type=TOKEN_KEYWORD_IF;    return TOKEN_KEYWORD_IF;}
"else"                  {now.type=TOKEN_KEYWORD_ELSE;  return TOKEN_KEYWORD_ELSE;}
"var"                   {now.type=TOKEN_KEYWORD_VAR;   return TOKEN_KEYWORD_VAR;}
"return"                {now.type=TOKEN_KEYWORD_RETURN;return TOKEN_KEYWORD_RETURN;}
[A-Za-z_]+[0-9a-zA-Z_]* {now.type=TOKEN_ID;now.value=yytext; return TOKEN_ID;}


"+"                     {now.type=TOKEN_ADD;          return TOKEN_ADD;}
"-"                     {now.type=TOKEN_SUB;          return TOKEN_SUB;}
"*"                     {now.type=TOKEN_MUL;          return TOKEN_MUL;}
"/"                     {now.type=TOKEN_DIV;          return TOKEN_DIV;}
"("                     {now.type=TOKEN_LP;           return TOKEN_LP;}
")"                     {now.type=TOKEN_RP;           return TOKEN_RP;}
"["                     {now.type=TOKEN_LSB;          return TOKEN_LSB;}
"]"                     {now.type=TOKEN_RSB;          return TOKEN_RSB;}
"{"                     {now.type=TOKEN_LB;           return TOKEN_LB;}
"}"                     {now.type=TOKEN_RB;           return TOKEN_RB;}
"\""                    {BEGIN STRING;}//{now.type=TOKEN_DQ;           return TOKEN_DQ;}
"\'"                    {BEGIN SINGLE_STRING;}//{now.type=TOKEN_SQ;           return TOKEN_SQ;}
";"                     {now.type=TOKEN_SEM;          return TOKEN_SEM;}
":"                     {now.type=TOKEN_COL;          return TOKEN_COL;}
"=="                    {now.type=TOKEN_EQU;          return TOKEN_EQU;}
"!="                    {now.type=TOKEN_NOT_EQU;      return TOKEN_NOT_EQU;}
"->"                    {now.type=TOKEN_ARROW;        return TOKEN_ARROW;}
"<="                    {now.type=TOKEN_LTHAN_EQU;    return TOKEN_LTHAN_EQU;}
">="                    {now.type=TOKEN_MTHAN_EQU;    return TOKEN_MTHAN_EQU;}
"="                     {now.type=TOKEN_SET;          return TOKEN_SET;}
"<"                     {now.type=TOKEN_LTHAN;        return TOKEN_LTHAN;}
">"                     {now.type=TOKEN_MTHAN;        return TOKEN_MTHAN;}
"!"                     {now.type=TOKEN_NOT;          return TOKEN_NOT;}


<<EOF>>                 {return TOKEN_EOF;}
"//".*                  {}
"/*"                    {BEGIN COMMENT;}
<COMMENT>"*/"           {BEGIN INITIAL;}
<COMMENT>.              {}
<STRING>"\""            {BEGIN INITIAL;}
<STRING>[^\"]*?         {now.type=TOKEN_STRING;now.value=yytext; return TOKEN_STRING;}
<SINGLE_STRING>"\'"     {BEGIN INITIAL;}
<SINGLE_STRING>"\n"     {now.type=TOKEN_ERROR;        return TOKEN_ERROR;}
<SINGLE_STRING>[^\n & *\']*?      {now.type=TOKEN_STRING;now.value=yytext; return TOKEN_STRING;}


[0-9]+                  {now.type=TOKEN_CONST_INT;now.value=yytext; return TOKEN_CONST_INT;}
[0-9]+\.[0-9]+          {now.type=TOKEN_CONST_FLOAT;now.value=yytext; return TOKEN_CONST_FLOAT;}
.                       {printf("Unknown token %s",yytext);}
%%

int yyFlexLexer::yywrap(void){
    return true;
}
token getToken(){
    token tmp = now;
    now.type=0;
    now.value="";
    return tmp;
}
extern int main(int argc,char *argv[]);