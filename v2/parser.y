%{
    #include <cstdio>
    #include <string>
    #include <vector>
    #include "ast.hpp"
    BlockAST *program_block;

    extern int yylex();
    

    void yyerror(const char *s){
        fprintf(stderr,"Error: %s",s);
        return;
    }
%}

//Parser Data structure

%union{
    ASTBase *node;
    BlockAST *block;
    ExpressionAST *expression;
    StatementAST *statement;
    IdentifierAST *identifier;
    VariableDeclarationAST *var_decl;
    
    std::vector<VariableDeclarationAST*> *varvec;
    std::vector<ExpressionAST*> *exprvec;

    std::string *string;
    int token;
}

//terminal symbols (tokens).
%token <string> Identifier_t Integer_t Double_t
%token <token> CEQ/*==*/ 
%token <token> CNE/*!=*/
%token <token> CLT/*<*/
%token <token> CLE/*<=*/
%token <token> CGT/*>*/
%token <token> CGE/*>=*/
%token <token> EQUAL/*=*/

%token <token> LPAREN/*(*/ 
%token <token> RPAREN/*)*/
%token <token> LBRACE/*{*/
%token <token> RBRACE/*}*/
%token <token> DOT/*.*/
%token <token> COMMA/*,*/
%token <token> PLUS/*+*/
%token <token> MINUS/*-*/
%token <token> MUL/***/
%token <token> DIV/*/*/

/*nonterminal symbols */
%type <identifier> identifier
%type <expression> numeric expression
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <block> program statements block
%type <statement> statement var_decl func_decl
%type <token> comparison

/*mathematical operators */

%left PLUS MINUS MUL DIV

%start program

%%
program : statements { program_block = $1; }
        ;

statements  : statement { $$ = new BlockAST(); $$->statements.push_back($<statement>1);}
            | statements statement { $1->statements.push_back($<statement>2); }
            ;

statement   : var_decl | func_decl
            | expression { $$ = new ExpressionASTStatement(*$1);}
            ;
block   : LBRACE statements RBRACE { $$ = $2;}
        | LBRACE RBRACE {$$ = new BlockAST();}
        ;

var_decl : identifier identifier { $$ = new VariableDeclarationAST(*$1,*$2); }
         | identifier identifier EQUAL expression {$$ = new VariableDeclarationAST(*$1,*$2,$4);}
         ;

func_decl : identifier identifier LPAREN func_decl_args RPAREN block 
            { $$ = new FunctionDeclarationAST(*$1, *$2, *$4, *$6); delete $4; }
          ;
    
func_decl_args : /*blank*/  { $$ = new VariableList(); }
          | var_decl { $$ = new VariableList(); $$->push_back($<var_decl>1); }
          | func_decl_args COMMA var_decl { $1->push_back($<var_decl>3); }
          ;

identifier : Identifier_t { $$ = new IdentifierAST(*$1); delete $1; }
      ;

numeric : Integer_t { $$ = new IntegerAST(atol($1->c_str())); delete $1; }
        | Double_t { $$ = new DoubleAST(atof($1->c_str())); delete $1; }
        ;
    
expression : identifier EQUAL expression { $$ = new AssignmentAST(*$<identifier>1, *$3); }
     | identifier LPAREN call_args RPAREN { $$ = new MethodCallAST(*$1, *$3); delete $3; }
     | identifier { $<identifier>$ = $1; }
     | numeric
     | expression comparison expression { $$ = new BinaryOperatorAST(*$1, $2, *$3); }
     | LPAREN expression RPAREN { $$ = $2; }
     ;
    
call_args : /*blank*/  { $$ = new ExpressionList(); }
          | expression { $$ = new ExpressionList(); $$->push_back($1); }
          | call_args COMMA expression  { $1->push_back($3); }
          ;

comparison : CEQ | CNE | CLT | CLE | CGT | CGE 
           | PLUS | MINUS | MUL | DIV
           ;

%%