/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_HPP_INCLUDED
# define YY_YY_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OP_ADD = 258,
    OP_SUB = 259,
    OP_MUL = 260,
    OP_DIV = 261,
    OP_LT = 262,
    OP_LE = 263,
    OP_GT = 264,
    OP_GE = 265,
    OP_EQ = 266,
    OP_NE = 267,
    OP_OR = 268,
    OP_AND = 269,
    RET_ARROW = 270,
    LET = 271,
    INT = 272,
    STRUCT = 273,
    IF = 274,
    ELSE = 275,
    WHILE = 276,
    RETURN = 277,
    FN = 278,
    CONTINUE = 279,
    BREAK = 280,
    ID = 281,
    NUM = 282,
    UMINUS = 283
  };
#endif
/* Tokens.  */
#define OP_ADD 258
#define OP_SUB 259
#define OP_MUL 260
#define OP_DIV 261
#define OP_LT 262
#define OP_LE 263
#define OP_GT 264
#define OP_GE 265
#define OP_EQ 266
#define OP_NE 267
#define OP_OR 268
#define OP_AND 269
#define RET_ARROW 270
#define LET 271
#define INT 272
#define STRUCT 273
#define IF 274
#define ELSE 275
#define WHILE 276
#define RETURN 277
#define FN 278
#define CONTINUE 279
#define BREAK 280
#define ID 281
#define NUM 282
#define UMINUS 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "parser.yacc"

	A_pos token;
	A_pos key; 	// 关键字
	A_exprUnit expr;
	A_type type;
	A_program prog;
	A_rightVal rightVal;
	A_arithExpr arithExpr;
	A_boolExpr boolExpr;
	A_arithBiOpExpr arithBiOpExpr;
	A_arithBiOp arithBiOp;
	A_arithUOp arithUOp;
	A_boolBiOp boolBiOp;
	A_arithUExpr arithUExpr;
	A_nativeType nativeType;
	A_exprUnit exprUnit;
	A_fnCall fnCall;
	A_comOp comOp;
	A_indexExpr indexExpr;
	A_arrayExpr arrayExpr;
	A_memberExpr memberExpr;
	A_boolUnit boolUnit;
	A_boolBiOpExpr boolBiOpExpr;
	A_boolUOpExpr boolUOpExpr;
	A_boolUOp boolUOp;
	A_comExpr comExpr;
	A_leftVal leftVal;
	A_assignStmt assignStmt;
	A_rightValList rightValList;
	A_varDefScalar varDefScalar;
	A_varDefArray varDefArray;
	A_varDeclScalar varDeclScalar;
	A_varDeclArray varDeclArray;
	A_varDecl varDecl;
	A_varDef varDef;
	A_varDeclStmt varDeclStmt;
	A_varDeclList varDeclList;
	A_structDef structDef;
	A_paramDecl paramDecl;
	A_fnDecl fnDecl;
	A_fnDef fnDef;
	A_codeBlockStmt codeBlockStmt;
	A_ifStmt ifStmt;
	A_whileStmt whileStmt;
	A_fnDeclStmt fnDeclStmt;
	A_callStmt callStmt;
	A_returnStmt returnStmt;
	A_programElement programElement;
	A_codeBlockStmtList codeBlockStmtList;
	A_programElementList programElementList;
	// A_tokenId tokenId;
	// A_tokenNum tokenNum;

#line 167 "y.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */
