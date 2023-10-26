%{
#include <stdio.h>
#include "TeaplAst.h"

extern A_pos pos;
extern A_program root;

extern int yylex(void);
extern "C"{
extern void yyerror(char *s); 
extern int  yywrap();
}

%}


%union{
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
}


%token <token> OP_ADD OP_SUB OP_MUL OP_DIV OP_LT OP_LE OP_GT OP_GE OP_EQ OP_NE OP_OR OP_AND '(' ')' '=' ',' ';' '{' '}' '.' '!' '[' ']' ':' RET_ARROW

%token <key> LET INT STRUCT IF ELSE WHILE RET FN CONTINUE BREAK

%token <expr> ID NUM


%right '='
%left OP_OR
%left OP_AND
%left OP_EQ OP_NE
%left OP_LE OP_LT OP_GT OP_GE
%left OP_ADD OP_SUB
%left OP_MUL OP_DIV
%right '!' UMINUS
%left '[' ']' '(' ')'
%left '.'
%right ELSE RET_ARROW


%type<prog> program 
%type<varDeclStmt> varDeclStmt
%type<programElement> programElement
%type<programElementList> programElementList
%type<assignStmt> assignStmt
%type<leftVal> leftVal
%type<indexExpr> indexExpr
%type<arrayExpr> arrayExpr
%type<rightValList> rightValList rightValListTail
%type<rightVal> rightVal
%type<memberExpr> memberExpr
%type<arithExpr> arithExpr
%type<arithBiOpExpr> arithBiOpExpr
%type<exprUnit> exprUnit
%type<arithUExpr> arithUExpr
%type<fnCall> fnCall
%type<boolBiOpExpr> boolBiOpExpr
%type<boolExpr> boolExpr
%type<comExpr> comExpr
%type<boolUOpExpr> boolUOpExpr
%type<boolUnit> boolUnit
%type<varDeclScalar> varDeclScalar
%type<varDeclArray> varDeclArray
%type<varDecl> varDecl
%type<type> type type_ret
%type<varDefArray> varDefArray
%type<varDef> varDef
%type<varDefScalar> defScalar
%type<varDeclList> varDeclList varDeclListTail
%type<structDef> structDef
%type<paramDecl> paramDeclList
%type<fnDecl> fnDecl //mainDecl
%type<codeBlockStmt> codeBlockStmt
%type<codeBlockStmtList> codeBlockStmtList codeBlock elseStmt
%type<callStmt> callStmt
%type<ifStmt> ifStmt
%type<whileStmt> whileStmt
%type<returnStmt> returnStmt
%type<arithBiOp> arithBiOp
%type<boolBiOp> boolBiOp
%type<comOp> comOp
%type<nativeType> nativeType
%type<fnDeclStmt> fnDeclStmt
%type<fnDef> fnDef // mainDef


%start program
%%
program : programElementList { root = A_Program($1); $$ = A_Program($1); }

programElementList 
	: programElement programElementList { $$ = A_ProgramElementList($1, $2); }
	| { $$ = NULL; }

programElement 
	: varDeclStmt { $$ = A_ProgramVarDeclStmt($1->pos, $1); }
	| structDef { $$ = A_ProgramStructDef($1->pos, $1); }
	| fnDeclStmt { $$ = A_ProgramFnDeclStmt($1->pos, $1); }
	| fnDef { $$ = A_ProgramFnDef($1->pos, $1); }
	| ';'  { $$ = A_ProgramNullStmt($1); }

assignStmt : leftVal '=' rightVal ';' { $$ = A_AssignStmt($1->pos, $1, $3); }

indexExpr : ID { $$ = A_IdIndexExpr($1->pos, $1->u.id); }
	| NUM { $$ = A_NumIndexExpr($1->pos, $1->u.num); }

arrayExpr : ID '[' indexExpr ']' { $$ = A_ArrayExpr($1->pos, $1->u.id, $3); }	

memberExpr : ID '.' ID { $$ = A_MemberExpr($1->pos, $1->u.id, $3->u.id); }

leftVal : ID  { $$ = A_IdExprLVal($1->pos, $1->u.id); }
	| arrayExpr { $$ = A_ArrExprLVal($1->pos, $1); }
	| memberExpr { $$ = A_MemberExprLVal($1->pos, $1); }


rightVal : arithExpr { $$ = A_ArithExprRVal($1->pos, $1); }
	| boolExpr { $$ = A_BoolExprRVal($1->pos, $1); }
	
arithBiOpExpr : arithExpr arithBiOp arithExpr { $$ = A_ArithBiOpExpr($1->pos, $2, $1, $3); }

arithExpr : arithBiOpExpr { $$ = A_ArithBiOp_Expr($1->pos, $1); }
	| exprUnit { $$ = A_ExprUnit($1->pos, $1); }

arithBiOp : OP_ADD { $$ = A_add; }
	| OP_SUB { $$ = A_sub; } 
	| OP_MUL { $$ = A_mul; } 
	| OP_DIV { $$ = A_div; }

arithUExpr : OP_SUB exprUnit { $$ = A_ArithUExpr($1, A_neg, $2); }

exprUnit : NUM { $$ = $1; }
	| ID { $$ = $1; }
	| '(' arithExpr ')' { $$ = A_ArithExprUnit($2->pos, $2); }
	| fnCall { $$ = A_CallExprUnit($1->pos, $1); }
	| arrayExpr { $$ = A_ArrayExprUnit($1->pos, $1); }
	| memberExpr { $$ = A_MemberExprUnit($1->pos, $1); }
	| arithUExpr %prec UMINUS { $$ = A_ArithUExprUnit($1->pos, $1); }

fnCall : ID '(' rightValList')' { $$ = A_FnCall($1->pos, $1->u.id, $3); }

boolBiOpExpr 
	: boolExpr boolBiOp boolExpr { $$ = A_BoolBiOpExpr($1->pos, $2, $1, $3); }

boolExpr : boolBiOpExpr { $$ = A_BoolBiOp_Expr($1->pos, $1); }
	| boolUnit { $$ = A_BoolExpr($1->pos, $1); }

comExpr : exprUnit comOp exprUnit { $$ = A_ComExpr($1->pos, $2, $1, $3); }

boolUOpExpr : '!' boolUnit { $$ = A_BoolUOpExpr($1, A_not, $2); }

boolUnit : comExpr { $$ = A_ComExprUnit($1->pos, $1); }
	| '(' boolExpr ')' { $$ = A_BoolExprUnit($1, $2); }
	| boolUOpExpr { $$ = A_BoolUOpExprUnit($1->pos, $1); }

boolBiOp : OP_AND { $$ = A_and; }
	| OP_OR { $$ = A_or; }

comOp : OP_LT { $$ = A_lt; }
	| OP_LE { $$ = A_le; }
	| OP_GT { $$ = A_gt; }
	| OP_GE { $$ = A_ge; }
	| OP_EQ { $$ = A_eq; }
	| OP_NE { $$ = A_ne; }

rightValListTail : ',' rightVal rightValListTail { $$ = A_RightValList($2, $3); }
	| { $$ = NULL; }

rightValList : rightVal rightValListTail { $$ = A_RightValList($1, $2); }
	| { $$ = NULL; }

varDeclStmt 
	: LET varDecl ';' { $$ = A_VarDeclStmt($1, $2); }
	| LET varDef ';' { $$ = A_VarDefStmt($1, $2); }

varDeclScalar : ID type { $$ = A_VarDeclScalar($1->pos, $1->u.id, $2); }

varDeclArray : ID '[' NUM ']' type { $$ = A_VarDeclArray($1->pos, $1->u.id, $3->u.num, $5); }

varDecl : varDeclScalar { $$ = A_VarDecl_Scalar($1->pos, $1); }
	| varDeclArray { $$ = A_VarDecl_Array($1->pos, $1); }

defScalar : ID type '=' rightVal { $$ = A_VarDefScalar($1->pos, $1->u.id, $2, $4); }

varDefArray : ID '[' NUM ']' type '=' '{' rightValList '}' { $$ = A_VarDefArray($1->pos, $1->u.id, $3->u.num, $5, $8); }

varDef : defScalar { $$ = A_VarDef_Scalar($1->pos, $1); }
	| varDefArray { $$ = A_VarDef_Array($1->pos, $1); }

type : ':' nativeType { $$ = A_NativeType($1, $2); }
	| ':' ID { $$ = A_StructType($1, $2->u.id); }
	| { $$ = NULL; }

type_ret : RET_ARROW nativeType { $$ = A_NativeType($1, $2); }
	| RET_ARROW ID { $$ = A_StructType($1, $2->u.id); }
	| { $$ = NULL; }

nativeType : INT { $$ = A_intTypeKind; }

varDeclListTail : ',' varDecl varDeclListTail { $$ = A_VarDeclList($2, $3); }
	| { $$ = NULL; }

varDeclList : varDecl varDeclListTail { $$ = A_VarDeclList($1, $2); }
	| { $$ = NULL; }

structDef : STRUCT ID '{' varDeclList '}' { $$ = A_StructDef($1, $2->u.id, $4); }

fnDeclStmt : fnDecl ';' { $$ = A_FnDeclStmt($1->pos, $1); }

paramDeclList : varDeclList { $$ = A_ParamDecl($1); }

fnDecl : FN ID '(' paramDeclList ')' type_ret { $$ = A_FnDecl($1, $2->u.id, $4, $6); }

fnDef : fnDecl codeBlock { $$ = A_FnDef($1->pos, $1, $2); }

codeBlockStmt : varDeclStmt { $$ = A_BlockVarDeclStmt($1->pos, $1); }
	| assignStmt { $$ = A_BlockAssignStmt($1->pos, $1); }
	| callStmt { $$ = A_BlockCallStmt($1->pos, $1); }
	| ifStmt { $$ = A_BlockIfStmt($1->pos, $1); }
	| whileStmt { $$ = A_BlockWhileStmt($1->pos, $1); }
	| returnStmt { $$ = A_BlockReturnStmt($1->pos, $1); }
	| CONTINUE ';' { $$ = A_BlockContinueStmt($1); }
	| BREAK ';' { $$ = A_BlockBreakStmt($1); }
	| ';' { $$ = A_BlockNullStmt($1); } //?

codeBlockStmtList : codeBlockStmt codeBlockStmtList { $$ = A_CodeBlockStmtList($1, $2); }
	| { $$ = NULL; }

codeBlock : '{' codeBlockStmtList '}' { $$ = $2; }

callStmt : fnCall ';' { $$ = A_CallStmt($1->pos, $1); }

elseStmt : ELSE codeBlock { $$ = $2; }
	| { $$ = NULL; }

ifStmt : IF '(' boolExpr ')' codeBlock elseStmt { $$ = A_IfStmt($1, $3, $5, $6); }

whileStmt : WHILE '(' boolExpr ')' codeBlock { $$ = A_WhileStmt($1, $3, $5); }

returnStmt : RET rightVal ';' { $$ = A_ReturnStmt($1, $2); }
%%

extern "C"{
void yyerror(char * s)
{
  fprintf(stderr, "%s\n",s);
}
int yywrap()
{
  return(1);
}
}


