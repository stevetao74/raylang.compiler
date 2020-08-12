#include <string>
using token_type = enum {
    TOKEN_ADD=0,
    TOKEN_SUB=1,
    TOKEN_MUL=2,
    TOKEN_DIV=3,
    TOKEN_EOF=4,
    TOKEN_ID=5,
    TOKEN_LP=6,//(
    TOKEN_RP=7,//)
    TOKEN_LB=8,//{
    TOKEN_RB=9,//}
    TOKEN_LSB=10,//[
    TOKEN_RSB=11,//]
    TOKEN_DQ=12,//"
    TOKEN_SQ=13,//'
    TOKEN_SEM=14,//;
    TOKEN_COL=15,//:
    TOKEN_SET=16,//=
    TOKEN_EQU=17,//==
    TOKEN_LTHAN=18,//<
    TOKEN_MTHAN=19,//>
    TOKEN_LTHAN_EQU=20,//<=
    TOKEN_MTHAN_EQU=21,//>=
    TOKEN_NOT_EQU=22,//!=
    TOKEN_NOT=23,//!
    TOKEN_ARROW=24,//->

    TOKEN_KEYWORD_FUNC=216,
    TOKEN_KEYWORD_IF=217,
    TOKEN_KEYWORD_ELSE=218,
    TOKEN_KEYWORD_VAR=219,
    TOKEN_KEYWORD_RETURN=220,
    TOKEN_KEYWORD_GET=221, 
    TOKEN_KEYWORD_AS=222, 
    
    TOKEN_CONST_INT=100,
    TOKEN_CONST_FLOAT=101
};
using token = struct
{
    int type;
    std::string value = "";
};
token getToken();