/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.yacc"

#include <stdio.h>
#include "TeaplAst.h"

extern A_pos pos;
extern A_program root;

extern int yylex(void);
extern "C"{
extern void yyerror(char *s); 
extern int  yywrap();
}


#line 85 "y.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    RET = 277,
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
#define RET 277
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

#line 247 "y.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   161

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

#define YYUNDEFTOK  2
#define YYMAXUTOK   283


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,     2,     2,     2,     2,     2,
      15,    16,     2,     2,    18,     2,    22,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,    19,
       2,    17,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    20,     2,    21,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   140,   140,   143,   144,   147,   148,   149,   150,   151,
     153,   155,   156,   158,   160,   162,   163,   164,   167,   168,
     170,   172,   173,   175,   176,   177,   178,   180,   182,   183,
     184,   185,   186,   187,   188,   190,   193,   195,   196,   198,
     200,   202,   203,   204,   206,   207,   209,   210,   211,   212,
     213,   214,   216,   217,   219,   220,   223,   224,   226,   228,
     230,   231,   233,   235,   237,   238,   240,   241,   242,   244,
     245,   246,   248,   250,   251,   253,   254,   256,   258,   260,
     262,   264,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   276,   277,   279,   281,   283,   284,   286,   288,   290
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OP_ADD", "OP_SUB", "OP_MUL", "OP_DIV",
  "OP_LT", "OP_LE", "OP_GT", "OP_GE", "OP_EQ", "OP_NE", "OP_OR", "OP_AND",
  "'('", "')'", "'='", "','", "';'", "'{'", "'}'", "'.'", "'!'", "'['",
  "']'", "':'", "RET_ARROW", "LET", "INT", "STRUCT", "IF", "ELSE", "WHILE",
  "RET", "FN", "CONTINUE", "BREAK", "ID", "NUM", "UMINUS", "$accept",
  "program", "programElementList", "programElement", "assignStmt",
  "indexExpr", "arrayExpr", "memberExpr", "leftVal", "rightVal",
  "arithBiOpExpr", "arithExpr", "arithBiOp", "arithUExpr", "exprUnit",
  "fnCall", "boolBiOpExpr", "boolExpr", "comExpr", "boolUOpExpr",
  "boolUnit", "boolBiOp", "comOp", "rightValListTail", "rightValList",
  "varDeclStmt", "varDeclScalar", "varDeclArray", "varDecl", "defScalar",
  "varDefArray", "varDef", "type", "type_ret", "nativeType",
  "varDeclListTail", "varDeclList", "structDef", "fnDeclStmt",
  "paramDeclList", "fnDecl", "fnDef", "codeBlockStmt", "codeBlockStmtList",
  "codeBlock", "callStmt", "elseStmt", "ifStmt", "whileStmt", "returnStmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,    40,    41,    61,    44,    59,
     123,   125,    46,    33,    91,    93,    58,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283
};
# endif

#define YYPACT_NINF (-123)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       4,  -123,   -19,    -8,    20,    42,  -123,     4,  -123,  -123,
    -123,    27,  -123,    74,  -123,  -123,    43,  -123,  -123,    46,
      56,    86,  -123,  -123,  -123,    33,  -123,    49,   -11,    75,
    -123,  -123,    65,    65,  -123,    93,    94,     2,    91,    95,
       7,  -123,  -123,  -123,    96,    97,  -123,    33,    90,  -123,
    -123,  -123,  -123,    87,  -123,  -123,  -123,     2,    78,    99,
      98,  -123,   102,     2,     2,     6,     2,     2,     7,  -123,
    -123,  -123,   101,  -123,    51,  -123,    70,  -123,  -123,    92,
    -123,  -123,  -123,  -123,  -123,     2,    84,    45,     2,  -123,
    -123,  -123,    89,  -123,    82,  -123,    65,  -123,  -123,   100,
      70,    73,    77,     6,  -123,    69,    83,  -123,  -123,  -123,
    -123,  -123,  -123,     6,  -123,  -123,  -123,  -123,  -123,  -123,
       6,  -123,  -123,     2,   105,   108,  -123,  -123,  -123,   103,
     106,   109,   104,    99,    -5,  -123,   110,   110,  -123,  -123,
    -123,    51,  -123,    92,     2,  -123,  -123,  -123,  -123,   111,
      89,  -123,  -123,  -123,   107,  -123,   105,     2,  -123,   110,
    -123,  -123,   112,  -123,  -123
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     9,     0,     0,     0,     0,     2,     4,     5,     6,
       7,     0,     8,    68,    60,    61,     0,    64,    65,     0,
       0,     0,     1,     3,    78,    92,    81,     0,     0,    58,
      56,    57,    76,    76,    90,     0,     0,     0,     0,     0,
      15,    83,    16,    17,     0,     0,    82,    92,     0,    84,
      85,    86,    87,     0,    72,    67,    66,     0,    68,    74,
       0,    79,     0,     0,     0,     0,     0,     0,    29,    28,
      32,    33,     0,    21,    18,    34,    22,    31,    37,    19,
      41,    43,    38,    88,    89,    55,     0,     0,     0,    94,
      91,    93,    68,    62,     0,    58,     0,    75,    77,    71,
       0,     0,     0,     0,    27,     0,     0,    40,    99,    23,
      24,    25,    26,     0,    46,    47,    48,    49,    50,    51,
       0,    45,    44,     0,    53,     0,    14,    11,    12,     0,
       0,    59,     0,    74,     0,    80,     0,     0,    22,    30,
      42,    20,    39,    36,     0,    54,    35,    13,    10,     0,
      68,    73,    70,    69,    96,    98,    53,    55,    59,     0,
      97,    52,     0,    95,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -123,  -123,   125,  -123,  -123,  -123,   -12,    -9,  -123,   -37,
    -123,   -54,  -123,  -123,   -60,     1,  -123,   -55,  -123,  -123,
      67,  -123,  -123,   -21,   -20,     3,  -123,  -123,    -1,  -123,
    -123,  -123,   -56,  -123,     8,     5,   113,  -123,  -123,  -123,
    -123,  -123,  -123,   114,  -122,  -123,  -123,  -123,  -123,  -123
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,    41,   129,    70,    71,    44,   124,
      73,    74,   113,    75,    76,    77,    78,    79,    80,    81,
      82,   123,   120,   145,   125,     8,    14,    15,    59,    17,
      18,    19,    29,   135,    56,    97,    60,     9,    10,    62,
      11,    12,    47,    48,    26,    49,   160,    50,    51,    52
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      72,    16,    95,   100,   100,   104,    65,   100,   101,   102,
      65,   106,   105,    42,   154,   155,    43,    66,    54,    13,
      93,   103,    85,     1,    54,    67,    45,    55,    46,    86,
      20,    87,     2,   152,     3,    42,   131,   163,    43,     4,
      68,    69,    22,   138,    68,    69,    24,    25,    45,   105,
      46,   130,    34,   138,   109,   110,   111,   112,    21,   141,
     142,     2,    30,   100,    35,    31,    36,    37,   143,    38,
      39,    40,   109,   110,   111,   112,    32,   114,   115,   116,
     117,   118,   119,   127,   128,   139,   121,   122,    53,   136,
     121,   122,    57,   137,   158,   133,   121,   122,    27,   140,
      28,    33,    94,    58,    28,   121,   122,   156,    63,    64,
      83,    91,    92,    88,    84,    28,    89,    96,    99,    98,
     108,   132,   126,   144,   146,   148,   149,   134,   147,   150,
      25,   157,    23,   164,   107,   161,     0,   162,   151,   159,
       0,     0,   153,     0,     0,     0,    61,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    90
};

static const yytype_int16 yycheck[] =
{
      37,     2,    58,    63,    64,    65,     4,    67,    63,    64,
       4,    66,    66,    25,   136,   137,    25,    15,    29,    38,
      57,    15,    15,    19,    29,    23,    25,    38,    25,    22,
      38,    24,    28,    38,    30,    47,    92,   159,    47,    35,
      38,    39,     0,   103,    38,    39,    19,    20,    47,   103,
      47,    88,    19,   113,     3,     4,     5,     6,    38,   113,
     120,    28,    19,   123,    31,    19,    33,    34,   123,    36,
      37,    38,     3,     4,     5,     6,    20,     7,     8,     9,
      10,    11,    12,    38,    39,    16,    13,    14,    39,    16,
      13,    14,    17,    16,   150,    96,    13,    14,    24,    16,
      26,    15,    24,    38,    26,    13,    14,   144,    15,    15,
      19,    21,    25,    17,    19,    26,    19,    18,    16,    21,
      19,    39,    38,    18,    16,    19,    17,    27,    25,    25,
      20,    20,     7,    21,    67,   156,    -1,   157,   133,    32,
      -1,    -1,   134,    -1,    -1,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    19,    28,    30,    35,    42,    43,    44,    66,    78,
      79,    81,    82,    38,    67,    68,    69,    70,    71,    72,
      38,    38,     0,    43,    19,    20,    85,    24,    26,    73,
      19,    19,    20,    15,    19,    31,    33,    34,    36,    37,
      38,    45,    47,    48,    49,    56,    66,    83,    84,    86,
      88,    89,    90,    39,    29,    38,    75,    17,    38,    69,
      77,    77,    80,    15,    15,     4,    15,    23,    38,    39,
      47,    48,    50,    51,    52,    54,    55,    56,    57,    58,
      59,    60,    61,    19,    19,    15,    22,    24,    17,    19,
      84,    21,    25,    50,    24,    73,    18,    76,    21,    16,
      55,    58,    58,    15,    55,    52,    58,    61,    19,     3,
       4,     5,     6,    53,     7,     8,     9,    10,    11,    12,
      63,    13,    14,    62,    50,    65,    38,    38,    39,    46,
      50,    73,    39,    69,    27,    74,    16,    16,    55,    16,
      16,    52,    55,    58,    18,    64,    16,    25,    19,    17,
      25,    76,    38,    75,    85,    85,    50,    20,    73,    32,
      87,    64,    65,    85,    21
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    44,    44,
      45,    46,    46,    47,    48,    49,    49,    49,    50,    50,
      51,    52,    52,    53,    53,    53,    53,    54,    55,    55,
      55,    55,    55,    55,    55,    56,    57,    58,    58,    59,
      60,    61,    61,    61,    62,    62,    63,    63,    63,    63,
      63,    63,    64,    64,    65,    65,    66,    66,    67,    68,
      69,    69,    70,    71,    72,    72,    73,    73,    73,    74,
      74,    74,    75,    76,    76,    77,    77,    78,    79,    80,
      81,    82,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    84,    84,    85,    86,    87,    87,    88,    89,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       4,     1,     1,     4,     3,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       3,     1,     1,     1,     1,     4,     3,     1,     1,     3,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     2,     0,     3,     3,     2,     5,
       1,     1,     4,     9,     1,     1,     2,     2,     0,     2,
       2,     0,     1,     3,     0,     2,     0,     5,     2,     1,
       6,     2,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     2,     0,     3,     2,     2,     0,     6,     5,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 140 "parser.yacc"
                             { root = A_Program((yyvsp[0].programElementList)); (yyval.prog) = A_Program((yyvsp[0].programElementList)); }
#line 1544 "y.tab.cpp"
    break;

  case 3:
#line 143 "parser.yacc"
                                            { (yyval.programElementList) = A_ProgramElementList((yyvsp[-1].programElement), (yyvsp[0].programElementList)); }
#line 1550 "y.tab.cpp"
    break;

  case 4:
#line 144 "parser.yacc"
          { (yyval.programElementList) = NULL; }
#line 1556 "y.tab.cpp"
    break;

  case 5:
#line 147 "parser.yacc"
                      { (yyval.programElement) = A_ProgramVarDeclStmt((yyvsp[0].varDeclStmt)->pos, (yyvsp[0].varDeclStmt)); }
#line 1562 "y.tab.cpp"
    break;

  case 6:
#line 148 "parser.yacc"
                    { (yyval.programElement) = A_ProgramStructDef((yyvsp[0].structDef)->pos, (yyvsp[0].structDef)); }
#line 1568 "y.tab.cpp"
    break;

  case 7:
#line 149 "parser.yacc"
                     { (yyval.programElement) = A_ProgramFnDeclStmt((yyvsp[0].fnDeclStmt)->pos, (yyvsp[0].fnDeclStmt)); }
#line 1574 "y.tab.cpp"
    break;

  case 8:
#line 150 "parser.yacc"
                { (yyval.programElement) = A_ProgramFnDef((yyvsp[0].fnDef)->pos, (yyvsp[0].fnDef)); }
#line 1580 "y.tab.cpp"
    break;

  case 9:
#line 151 "parser.yacc"
               { (yyval.programElement) = A_ProgramNullStmt((yyvsp[0].token)); }
#line 1586 "y.tab.cpp"
    break;

  case 10:
#line 153 "parser.yacc"
                                      { (yyval.assignStmt) = A_AssignStmt((yyvsp[-3].leftVal)->pos, (yyvsp[-3].leftVal), (yyvsp[-1].rightVal)); }
#line 1592 "y.tab.cpp"
    break;

  case 11:
#line 155 "parser.yacc"
               { (yyval.indexExpr) = A_IdIndexExpr((yyvsp[0].expr)->pos, (yyvsp[0].expr)->u.id); }
#line 1598 "y.tab.cpp"
    break;

  case 12:
#line 156 "parser.yacc"
              { (yyval.indexExpr) = A_NumIndexExpr((yyvsp[0].expr)->pos, (yyvsp[0].expr)->u.num); }
#line 1604 "y.tab.cpp"
    break;

  case 13:
#line 158 "parser.yacc"
                                 { (yyval.arrayExpr) = A_ArrayExpr((yyvsp[-3].expr)->pos, (yyvsp[-3].expr)->u.id, (yyvsp[-1].indexExpr)); }
#line 1610 "y.tab.cpp"
    break;

  case 14:
#line 160 "parser.yacc"
                       { (yyval.memberExpr) = A_MemberExpr((yyvsp[-2].expr)->pos, (yyvsp[-2].expr)->u.id, (yyvsp[0].expr)->u.id); }
#line 1616 "y.tab.cpp"
    break;

  case 15:
#line 162 "parser.yacc"
              { (yyval.leftVal) = A_IdExprLVal((yyvsp[0].expr)->pos, (yyvsp[0].expr)->u.id); }
#line 1622 "y.tab.cpp"
    break;

  case 16:
#line 163 "parser.yacc"
                    { (yyval.leftVal) = A_ArrExprLVal((yyvsp[0].arrayExpr)->pos, (yyvsp[0].arrayExpr)); }
#line 1628 "y.tab.cpp"
    break;

  case 17:
#line 164 "parser.yacc"
                     { (yyval.leftVal) = A_MemberExprLVal((yyvsp[0].memberExpr)->pos, (yyvsp[0].memberExpr)); }
#line 1634 "y.tab.cpp"
    break;

  case 18:
#line 167 "parser.yacc"
                     { (yyval.rightVal) = A_ArithExprRVal((yyvsp[0].arithExpr)->pos, (yyvsp[0].arithExpr)); }
#line 1640 "y.tab.cpp"
    break;

  case 19:
#line 168 "parser.yacc"
                   { (yyval.rightVal) = A_BoolExprRVal((yyvsp[0].boolExpr)->pos, (yyvsp[0].boolExpr)); }
#line 1646 "y.tab.cpp"
    break;

  case 20:
#line 170 "parser.yacc"
                                              { (yyval.arithBiOpExpr) = A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, (yyvsp[-1].arithBiOp), (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr)); }
#line 1652 "y.tab.cpp"
    break;

  case 21:
#line 172 "parser.yacc"
                          { (yyval.arithExpr) = A_ArithBiOp_Expr((yyvsp[0].arithBiOpExpr)->pos, (yyvsp[0].arithBiOpExpr)); }
#line 1658 "y.tab.cpp"
    break;

  case 22:
#line 173 "parser.yacc"
                   { (yyval.arithExpr) = A_ExprUnit((yyvsp[0].exprUnit)->pos, (yyvsp[0].exprUnit)); }
#line 1664 "y.tab.cpp"
    break;

  case 23:
#line 175 "parser.yacc"
                   { (yyval.arithBiOp) = A_add; }
#line 1670 "y.tab.cpp"
    break;

  case 24:
#line 176 "parser.yacc"
                 { (yyval.arithBiOp) = A_sub; }
#line 1676 "y.tab.cpp"
    break;

  case 25:
#line 177 "parser.yacc"
                 { (yyval.arithBiOp) = A_mul; }
#line 1682 "y.tab.cpp"
    break;

  case 26:
#line 178 "parser.yacc"
                 { (yyval.arithBiOp) = A_div; }
#line 1688 "y.tab.cpp"
    break;

  case 27:
#line 180 "parser.yacc"
                             { (yyval.arithUExpr) = A_ArithUExpr((yyvsp[-1].token), A_neg, (yyvsp[0].exprUnit)); }
#line 1694 "y.tab.cpp"
    break;

  case 28:
#line 182 "parser.yacc"
               { (yyval.exprUnit) = (yyvsp[0].expr); }
#line 1700 "y.tab.cpp"
    break;

  case 29:
#line 183 "parser.yacc"
             { (yyval.exprUnit) = (yyvsp[0].expr); }
#line 1706 "y.tab.cpp"
    break;

  case 30:
#line 184 "parser.yacc"
                            { (yyval.exprUnit) = A_ArithExprUnit((yyvsp[-1].arithExpr)->pos, (yyvsp[-1].arithExpr)); }
#line 1712 "y.tab.cpp"
    break;

  case 31:
#line 185 "parser.yacc"
                 { (yyval.exprUnit) = A_CallExprUnit((yyvsp[0].fnCall)->pos, (yyvsp[0].fnCall)); }
#line 1718 "y.tab.cpp"
    break;

  case 32:
#line 186 "parser.yacc"
                    { (yyval.exprUnit) = A_ArrayExprUnit((yyvsp[0].arrayExpr)->pos, (yyvsp[0].arrayExpr)); }
#line 1724 "y.tab.cpp"
    break;

  case 33:
#line 187 "parser.yacc"
                     { (yyval.exprUnit) = A_MemberExprUnit((yyvsp[0].memberExpr)->pos, (yyvsp[0].memberExpr)); }
#line 1730 "y.tab.cpp"
    break;

  case 34:
#line 188 "parser.yacc"
                                  { (yyval.exprUnit) = A_ArithUExprUnit((yyvsp[0].arithUExpr)->pos, (yyvsp[0].arithUExpr)); }
#line 1736 "y.tab.cpp"
    break;

  case 35:
#line 190 "parser.yacc"
                                { (yyval.fnCall) = A_FnCall((yyvsp[-3].expr)->pos, (yyvsp[-3].expr)->u.id, (yyvsp[-1].rightValList)); }
#line 1742 "y.tab.cpp"
    break;

  case 36:
#line 193 "parser.yacc"
                                     { (yyval.boolBiOpExpr) = A_BoolBiOpExpr((yyvsp[-2].boolExpr)->pos, (yyvsp[-1].boolBiOp), (yyvsp[-2].boolExpr), (yyvsp[0].boolExpr)); }
#line 1748 "y.tab.cpp"
    break;

  case 37:
#line 195 "parser.yacc"
                        { (yyval.boolExpr) = A_BoolBiOp_Expr((yyvsp[0].boolBiOpExpr)->pos, (yyvsp[0].boolBiOpExpr)); }
#line 1754 "y.tab.cpp"
    break;

  case 38:
#line 196 "parser.yacc"
                   { (yyval.boolExpr) = A_BoolExpr((yyvsp[0].boolUnit)->pos, (yyvsp[0].boolUnit)); }
#line 1760 "y.tab.cpp"
    break;

  case 39:
#line 198 "parser.yacc"
                                  { (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, (yyvsp[-1].comOp), (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit)); }
#line 1766 "y.tab.cpp"
    break;

  case 40:
#line 200 "parser.yacc"
                           { (yyval.boolUOpExpr) = A_BoolUOpExpr((yyvsp[-1].token), A_not, (yyvsp[0].boolUnit)); }
#line 1772 "y.tab.cpp"
    break;

  case 41:
#line 202 "parser.yacc"
                   { (yyval.boolUnit) = A_ComExprUnit((yyvsp[0].comExpr)->pos, (yyvsp[0].comExpr)); }
#line 1778 "y.tab.cpp"
    break;

  case 42:
#line 203 "parser.yacc"
                           { (yyval.boolUnit) = A_BoolExprUnit((yyvsp[-2].token), (yyvsp[-1].boolExpr)); }
#line 1784 "y.tab.cpp"
    break;

  case 43:
#line 204 "parser.yacc"
                      { (yyval.boolUnit) = A_BoolUOpExprUnit((yyvsp[0].boolUOpExpr)->pos, (yyvsp[0].boolUOpExpr)); }
#line 1790 "y.tab.cpp"
    break;

  case 44:
#line 206 "parser.yacc"
                  { (yyval.boolBiOp) = A_and; }
#line 1796 "y.tab.cpp"
    break;

  case 45:
#line 207 "parser.yacc"
                { (yyval.boolBiOp) = A_or; }
#line 1802 "y.tab.cpp"
    break;

  case 46:
#line 209 "parser.yacc"
              { (yyval.comOp) = A_lt; }
#line 1808 "y.tab.cpp"
    break;

  case 47:
#line 210 "parser.yacc"
                { (yyval.comOp) = A_le; }
#line 1814 "y.tab.cpp"
    break;

  case 48:
#line 211 "parser.yacc"
                { (yyval.comOp) = A_gt; }
#line 1820 "y.tab.cpp"
    break;

  case 49:
#line 212 "parser.yacc"
                { (yyval.comOp) = A_ge; }
#line 1826 "y.tab.cpp"
    break;

  case 50:
#line 213 "parser.yacc"
                { (yyval.comOp) = A_eq; }
#line 1832 "y.tab.cpp"
    break;

  case 51:
#line 214 "parser.yacc"
                { (yyval.comOp) = A_ne; }
#line 1838 "y.tab.cpp"
    break;

  case 52:
#line 216 "parser.yacc"
                                                 { (yyval.rightValList) = A_RightValList((yyvsp[-1].rightVal), (yyvsp[0].rightValList)); }
#line 1844 "y.tab.cpp"
    break;

  case 53:
#line 217 "parser.yacc"
          { (yyval.rightValList) = NULL; }
#line 1850 "y.tab.cpp"
    break;

  case 54:
#line 219 "parser.yacc"
                                         { (yyval.rightValList) = A_RightValList((yyvsp[-1].rightVal), (yyvsp[0].rightValList)); }
#line 1856 "y.tab.cpp"
    break;

  case 55:
#line 220 "parser.yacc"
          { (yyval.rightValList) = NULL; }
#line 1862 "y.tab.cpp"
    break;

  case 56:
#line 223 "parser.yacc"
                          { (yyval.varDeclStmt) = A_VarDeclStmt((yyvsp[-2].key), (yyvsp[-1].varDecl)); }
#line 1868 "y.tab.cpp"
    break;

  case 57:
#line 224 "parser.yacc"
                         { (yyval.varDeclStmt) = A_VarDefStmt((yyvsp[-2].key), (yyvsp[-1].varDef)); }
#line 1874 "y.tab.cpp"
    break;

  case 58:
#line 226 "parser.yacc"
                        { (yyval.varDeclScalar) = A_VarDeclScalar((yyvsp[-1].expr)->pos, (yyvsp[-1].expr)->u.id, (yyvsp[0].type)); }
#line 1880 "y.tab.cpp"
    break;

  case 59:
#line 228 "parser.yacc"
                                   { (yyval.varDeclArray) = A_VarDeclArray((yyvsp[-4].expr)->pos, (yyvsp[-4].expr)->u.id, (yyvsp[-2].expr)->u.num, (yyvsp[0].type)); }
#line 1886 "y.tab.cpp"
    break;

  case 60:
#line 230 "parser.yacc"
                        { (yyval.varDecl) = A_VarDecl_Scalar((yyvsp[0].varDeclScalar)->pos, (yyvsp[0].varDeclScalar)); }
#line 1892 "y.tab.cpp"
    break;

  case 61:
#line 231 "parser.yacc"
                       { (yyval.varDecl) = A_VarDecl_Array((yyvsp[0].varDeclArray)->pos, (yyvsp[0].varDeclArray)); }
#line 1898 "y.tab.cpp"
    break;

  case 62:
#line 233 "parser.yacc"
                                 { (yyval.varDefScalar) = A_VarDefScalar((yyvsp[-3].expr)->pos, (yyvsp[-3].expr)->u.id, (yyvsp[-2].type), (yyvsp[0].rightVal)); }
#line 1904 "y.tab.cpp"
    break;

  case 63:
#line 235 "parser.yacc"
                                                           { (yyval.varDefArray) = A_VarDefArray((yyvsp[-8].expr)->pos, (yyvsp[-8].expr)->u.id, (yyvsp[-6].expr)->u.num, (yyvsp[-4].type), (yyvsp[-1].rightValList)); }
#line 1910 "y.tab.cpp"
    break;

  case 64:
#line 237 "parser.yacc"
                   { (yyval.varDef) = A_VarDef_Scalar((yyvsp[0].varDefScalar)->pos, (yyvsp[0].varDefScalar)); }
#line 1916 "y.tab.cpp"
    break;

  case 65:
#line 238 "parser.yacc"
                      { (yyval.varDef) = A_VarDef_Array((yyvsp[0].varDefArray)->pos, (yyvsp[0].varDefArray)); }
#line 1922 "y.tab.cpp"
    break;

  case 66:
#line 240 "parser.yacc"
                      { (yyval.type) = A_NativeType((yyvsp[-1].token), (yyvsp[0].nativeType)); }
#line 1928 "y.tab.cpp"
    break;

  case 67:
#line 241 "parser.yacc"
                 { (yyval.type) = A_StructType((yyvsp[-1].token), (yyvsp[0].expr)->u.id); }
#line 1934 "y.tab.cpp"
    break;

  case 68:
#line 242 "parser.yacc"
          { (yyval.type) = NULL; }
#line 1940 "y.tab.cpp"
    break;

  case 69:
#line 244 "parser.yacc"
                                { (yyval.type) = A_NativeType((yyvsp[-1].token), (yyvsp[0].nativeType)); }
#line 1946 "y.tab.cpp"
    break;

  case 70:
#line 245 "parser.yacc"
                       { (yyval.type) = A_StructType((yyvsp[-1].token), (yyvsp[0].expr)->u.id); }
#line 1952 "y.tab.cpp"
    break;

  case 71:
#line 246 "parser.yacc"
          { (yyval.type) = NULL; }
#line 1958 "y.tab.cpp"
    break;

  case 72:
#line 248 "parser.yacc"
                 { (yyval.nativeType) = A_intTypeKind; }
#line 1964 "y.tab.cpp"
    break;

  case 73:
#line 250 "parser.yacc"
                                              { (yyval.varDeclList) = A_VarDeclList((yyvsp[-1].varDecl), (yyvsp[0].varDeclList)); }
#line 1970 "y.tab.cpp"
    break;

  case 74:
#line 251 "parser.yacc"
          { (yyval.varDeclList) = NULL; }
#line 1976 "y.tab.cpp"
    break;

  case 75:
#line 253 "parser.yacc"
                                      { (yyval.varDeclList) = A_VarDeclList((yyvsp[-1].varDecl), (yyvsp[0].varDeclList)); }
#line 1982 "y.tab.cpp"
    break;

  case 76:
#line 254 "parser.yacc"
          { (yyval.varDeclList) = NULL; }
#line 1988 "y.tab.cpp"
    break;

  case 77:
#line 256 "parser.yacc"
                                          { (yyval.structDef) = A_StructDef((yyvsp[-4].key), (yyvsp[-3].expr)->u.id, (yyvsp[-1].varDeclList)); }
#line 1994 "y.tab.cpp"
    break;

  case 78:
#line 258 "parser.yacc"
                        { (yyval.fnDeclStmt) = A_FnDeclStmt((yyvsp[-1].fnDecl)->pos, (yyvsp[-1].fnDecl)); }
#line 2000 "y.tab.cpp"
    break;

  case 79:
#line 260 "parser.yacc"
                            { (yyval.paramDecl) = A_ParamDecl((yyvsp[0].varDeclList)); }
#line 2006 "y.tab.cpp"
    break;

  case 80:
#line 262 "parser.yacc"
                                              { (yyval.fnDecl) = A_FnDecl((yyvsp[-5].key), (yyvsp[-4].expr)->u.id, (yyvsp[-2].paramDecl), (yyvsp[0].type)); }
#line 2012 "y.tab.cpp"
    break;

  case 81:
#line 264 "parser.yacc"
                         { (yyval.fnDef) = A_FnDef((yyvsp[-1].fnDecl)->pos, (yyvsp[-1].fnDecl), (yyvsp[0].codeBlockStmtList)); }
#line 2018 "y.tab.cpp"
    break;

  case 82:
#line 266 "parser.yacc"
                            { (yyval.codeBlockStmt) = A_BlockVarDeclStmt((yyvsp[0].varDeclStmt)->pos, (yyvsp[0].varDeclStmt)); }
#line 2024 "y.tab.cpp"
    break;

  case 83:
#line 267 "parser.yacc"
                     { (yyval.codeBlockStmt) = A_BlockAssignStmt((yyvsp[0].assignStmt)->pos, (yyvsp[0].assignStmt)); }
#line 2030 "y.tab.cpp"
    break;

  case 84:
#line 268 "parser.yacc"
                   { (yyval.codeBlockStmt) = A_BlockCallStmt((yyvsp[0].callStmt)->pos, (yyvsp[0].callStmt)); }
#line 2036 "y.tab.cpp"
    break;

  case 85:
#line 269 "parser.yacc"
                 { (yyval.codeBlockStmt) = A_BlockIfStmt((yyvsp[0].ifStmt)->pos, (yyvsp[0].ifStmt)); }
#line 2042 "y.tab.cpp"
    break;

  case 86:
#line 270 "parser.yacc"
                    { (yyval.codeBlockStmt) = A_BlockWhileStmt((yyvsp[0].whileStmt)->pos, (yyvsp[0].whileStmt)); }
#line 2048 "y.tab.cpp"
    break;

  case 87:
#line 271 "parser.yacc"
                     { (yyval.codeBlockStmt) = A_BlockReturnStmt((yyvsp[0].returnStmt)->pos, (yyvsp[0].returnStmt)); }
#line 2054 "y.tab.cpp"
    break;

  case 88:
#line 272 "parser.yacc"
                       { (yyval.codeBlockStmt) = A_BlockContinueStmt((yyvsp[-1].key)); }
#line 2060 "y.tab.cpp"
    break;

  case 89:
#line 273 "parser.yacc"
                    { (yyval.codeBlockStmt) = A_BlockBreakStmt((yyvsp[-1].key)); }
#line 2066 "y.tab.cpp"
    break;

  case 90:
#line 274 "parser.yacc"
              { (yyval.codeBlockStmt) = A_BlockNullStmt((yyvsp[0].token)); }
#line 2072 "y.tab.cpp"
    break;

  case 91:
#line 276 "parser.yacc"
                                                    { (yyval.codeBlockStmtList) = A_CodeBlockStmtList((yyvsp[-1].codeBlockStmt), (yyvsp[0].codeBlockStmtList)); }
#line 2078 "y.tab.cpp"
    break;

  case 92:
#line 277 "parser.yacc"
          { (yyval.codeBlockStmtList) = NULL; }
#line 2084 "y.tab.cpp"
    break;

  case 93:
#line 279 "parser.yacc"
                                      { (yyval.codeBlockStmtList) = (yyvsp[-1].codeBlockStmtList); }
#line 2090 "y.tab.cpp"
    break;

  case 94:
#line 281 "parser.yacc"
                      { (yyval.callStmt) = A_CallStmt((yyvsp[-1].fnCall)->pos, (yyvsp[-1].fnCall)); }
#line 2096 "y.tab.cpp"
    break;

  case 95:
#line 283 "parser.yacc"
                          { (yyval.codeBlockStmtList) = (yyvsp[0].codeBlockStmtList); }
#line 2102 "y.tab.cpp"
    break;

  case 96:
#line 284 "parser.yacc"
          { (yyval.codeBlockStmtList) = NULL; }
#line 2108 "y.tab.cpp"
    break;

  case 97:
#line 286 "parser.yacc"
                                                { (yyval.ifStmt) = A_IfStmt((yyvsp[-5].key), (yyvsp[-3].boolExpr), (yyvsp[-1].codeBlockStmtList), (yyvsp[0].codeBlockStmtList)); }
#line 2114 "y.tab.cpp"
    break;

  case 98:
#line 288 "parser.yacc"
                                             { (yyval.whileStmt) = A_WhileStmt((yyvsp[-4].key), (yyvsp[-2].boolExpr), (yyvsp[0].codeBlockStmtList)); }
#line 2120 "y.tab.cpp"
    break;

  case 99:
#line 290 "parser.yacc"
                              { (yyval.returnStmt) = A_ReturnStmt((yyvsp[-2].key), (yyvsp[-1].rightVal)); }
#line 2126 "y.tab.cpp"
    break;


#line 2130 "y.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 291 "parser.yacc"


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


