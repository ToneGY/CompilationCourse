%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TeaplAst.h"
#include "y.tab.hpp"
extern int line, col;
%}

%s COMMENT1
%s COMMENT2
%%
<COMMENT1>"\n"|"\r\n" { ++line; col=1; BEGIN INITIAL; }
<COMMENT1>. { col+=yyleng; }

<COMMENT2>"*/" { col+=yyleng; BEGIN INITIAL; }
<COMMENT2>"\n"|"\r\n" { ++line; col=1; }
<COMMENT2>. { col+=yyleng; }

<INITIAL>"\n" { ++line; col = 1; }
<INITIAL>" "|"\r"|"\t"|"\r" { col += yyleng; }

<INITIAL>"+" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_ADD;}
<INITIAL>"-" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_SUB;}
<INITIAL>"*" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_MUL;}
<INITIAL>"/" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_DIV;}

<INITIAL>"==" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_EQ;}
<INITIAL>"!=" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_NE;}
<INITIAL>"<" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_LT;}
<INITIAL>"<=" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_LE;}
<INITIAL>">" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_GT;}
<INITIAL>">=" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_GE;}

<INITIAL>"&&" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_AND;}
<INITIAL>"||" {yylval.token = A_Pos(line, col); col+=yyleng; return OP_OR;}


<INITIAL>"let"    { yylval.key=A_Pos(line,col); col+=yyleng; return LET; }
<INITIAL>"int"    { yylval.key=A_Pos(line,col); col+=yyleng; return INT; }
<INITIAL>"struct" { yylval.key=A_Pos(line,col); col+=yyleng; return STRUCT; }
<INITIAL>"fn"     { yylval.key=A_Pos(line,col); col+=yyleng; return FN; }
<INITIAL>"ret"    { yylval.key=A_Pos(line,col); col+=yyleng; return RETURN; }
<INITIAL>"if"     { yylval.key=A_Pos(line,col); col+=yyleng; return IF; }
<INITIAL>"else"   { yylval.key=A_Pos(line,col); col+=yyleng; return ELSE; }
<INITIAL>"while"  { yylval.key=A_Pos(line,col); col+=yyleng; return WHILE; }

<INITIAL>"continue" { yylval.key=A_Pos(line,col); col+=yyleng; return CONTINUE; }
<INITIAL>"break"    { yylval.key=A_Pos(line,col); col+=yyleng; return BREAK; }

<INITIAL>"->" { yylval.key=A_Pos(line,col); col+=yyleng; return RET_ARROW; }

<INITIAL>"//" {col+=yyleng;BEGIN COMMENT1;}
<INITIAL>"/*" {col+=yyleng;BEGIN COMMENT2;}

<INITIAL>"("|")"|":"|"="|","|";"|"{"|"}"|"."|"!"|"["|"]" { 
    yylval.token = A_Pos(line, col); 
    col += yyleng; 
    char c = yytext[0]; 
    return c; 
}

<INITIAL>[a-zA-Z_][a-zA-Z0-9_]* {
    char* p = (char*)malloc(strlen(yytext) + 1);
    if (!p) {
        fprintf(stderr,"\nout of memory!\n");
        exit(1);
    }
    strcpy(p, yytext);
    yylval.expr = A_IdExprUnit(A_Pos(line,col), p);
    col+=yyleng; 
    return ID;
}

<INITIAL>[1-9][0-9]*|0 {
    yylval.expr = A_NumExprUnit(A_Pos(line,col), atoi(yytext));
    col+=yyleng; 
    return NUM;
}



<INITIAL>. {
    col+=yyleng;
    printf("Illegal input \"%c\"\n", yytext[0]);
}
%%