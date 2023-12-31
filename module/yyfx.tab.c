
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "yyfx.y"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAXMEMBER 100

#define INTTYPE  0
#define REALTYPE 1

FILE *yyfx;  //指向输出文件的指针
FILE *yffx; //指向yffx.txt
extern int yylex();
extern FILE* yyin;
extern int row_num, col_num;

extern char key[20];
int VarCount=0;//变量个数

int NXQ=0; //指向下一个将要生成的四元式

int Entry(char *name);                        //如果符号表里没有放入符号表，主要是放标识符和常量
int NewTemp();                                 //产生Tx的随机变量并输入符号表
int Merge(int p,int q);                       //把两条链首合为一条，返回合并后的链首值
void BackPatch(int p,int t);               //回填
int GEN(char* op,int a1,int a2,int re);       //生成四元式    
void OutputQ();                               //输出四元式 

int FillType(int first,int type);             //符号表中first之后的类型都是type
int yyparse();								//调用语法分析程序
int yyerror(char *errstr);

struct QUATERLIST{
	char op[6];
	int arg1;
	int arg2;
	int result;
} QuaterList[MAXMEMBER];

struct VARLIST{
	char name[20];//名字
	int type;//类型
	int addr;//地址
} VarList[MAXMEMBER];



/* Line 189 of yacc.c  */
#line 122 "yyfx.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     Iden = 300,
     IntNo = 301,
     RealNo = 302,
     Program = 400,
     Begin = 401,
     End = 402,
     Var = 403,
     Integer = 404,
     Real = 405,
     While = 406,
     If = 407,
     Then = 408,
     Else = 409,
     LE = 500,
     GE = 501,
     NE = 502,
     UMINUS = 504
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 53 "yyfx.y"

    int  Iv;//标识符值
    int CH;//next链
    int NO;//常数值
    struct { int TC,FC;} _BExpr;//truelist，falselist
    struct { int QUAD,CH;} _WBD;//while
    struct { int type,place;} _Expr;//bool
	
    char   _Rop[5];
    int      First;
    char   str[20];



/* Line 214 of yacc.c  */
#line 192 "yyfx.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 204 "yyfx.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   118

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNRULES -- Number of states.  */
#define YYNSTATES  100

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   504

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    21,     2,     2,     2,    29,    20,     2,
      34,    35,    27,    25,    32,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    33,    31,
      22,    24,    23,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    19,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     4,     5,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      16,    17,    18,     2,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,    10,    14,    17,    21,    24,    28,
      31,    38,    44,    46,    48,    50,    52,    57,    61,    65,
      69,    73,    77,    81,    84,    86,    88,    90,    93,    96,
      99,   102,   106,   112,   117,   122,   124,   128,   132,   133,
     138,   139,   144,   147,   151,   153,   155,   157,   159,   161,
     163,   165
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    41,     7,    49,     8,    -1,
      41,     9,    42,    -1,     9,    42,    -1,    42,    43,    31,
      -1,    43,    31,    -1,    43,    32,    46,    -1,    44,    46,
      -1,    43,    32,    45,    33,    24,    48,    -1,    44,    45,
      33,    24,    48,    -1,    10,    -1,    11,    -1,    46,    -1,
       3,    -1,    45,    33,    24,    48,    -1,    48,    25,    48,
      -1,    48,    26,    48,    -1,    48,    27,    48,    -1,    48,
      28,    48,    -1,    48,    29,    48,    -1,    34,    48,    35,
      -1,    26,    48,    -1,    46,    -1,    59,    -1,    50,    -1,
      50,    49,    -1,    47,    31,    -1,    51,    55,    -1,    53,
      55,    -1,    52,    55,    15,    -1,    13,    34,    56,    35,
      14,    -1,    13,    34,    56,    35,    -1,    54,    34,    56,
      35,    -1,    12,    -1,    36,    49,    37,    -1,    48,    60,
      48,    -1,    -1,    56,    20,    57,    56,    -1,    -1,    56,
      19,    58,    56,    -1,    21,    56,    -1,    34,    56,    35,
      -1,     4,    -1,     5,    -1,    22,    -1,    23,    -1,    24,
      -1,    17,    -1,    18,    -1,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   125,   131,   136,   141,   142,   144,   149,
     155,   174,   195,   200,   208,   210,   217,   238,   268,   299,
     329,   357,   368,   373,   381,   388,   397,   402,   408,   413,
     418,   429,   435,   440,   446,   452,   456,   463,   470,   470,
     475,   475,   482,   487,   493,   500,   508,   509,   510,   511,
     512,   513
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Iden", "IntNo", "RealNo", "Program",
  "Begin", "End", "Var", "Integer", "Real", "While", "If", "Then", "Else",
  "LE", "GE", "NE", "'|'", "'&'", "'!'", "'<'", "'>'", "'='", "'+'", "'-'",
  "'*'", "'/'", "'%'", "UMINUS", "';'", "','", "':'", "'('", "')'", "'['",
  "']'", "$accept", "ProgDef", "SubProg", "VarDef", "VarDefList",
  "VarList", "Type", "Asign_Varable", "Varable", "AsignState", "Expr",
  "StateList", "Statement", "I_T_E", "I_T", "Wd", "W", "ComplexState",
  "BoolExpr", "$@1", "$@2", "Const", "RelationOp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   503,   300,   301,   302,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   500,   501,   502,   124,
      38,    33,    60,    62,    61,    43,    45,    42,    47,    37,
     504,    59,    44,    58,    40,    41,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    41,    41,    42,    42,    43,    43,
      43,    43,    44,    44,    45,    46,    47,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    49,    49,    50,    50,
      50,    51,    52,    52,    53,    54,    55,    56,    57,    56,
      58,    56,    56,    56,    59,    59,    60,    60,    60,    60,
      60,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     4,     3,     2,     3,     2,     3,     2,
       6,     5,     1,     1,     1,     1,     4,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     2,     2,     2,
       2,     3,     5,     4,     4,     1,     3,     3,     0,     4,
       0,     4,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,    12,    13,     5,     0,     0,
       1,     0,     0,     0,     7,     0,    15,     0,     9,    35,
       0,     0,    14,     0,     0,    26,     0,     0,     0,     0,
       4,     6,     0,     8,     0,     0,     0,    28,     3,    27,
       0,    29,     0,    30,     0,     0,     0,    44,    45,     0,
       0,     0,    24,     0,     0,    25,     0,     0,    31,     0,
       0,     0,    11,    42,    23,     0,     0,    51,    49,    50,
      46,    47,    48,     0,     0,     0,     0,     0,     0,    40,
      38,    33,    16,    36,    34,    10,     0,    22,    43,    17,
      18,    19,    20,    21,    37,     0,     0,    32,    41,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,     7,     8,     9,    21,    52,    23,
      53,    24,    25,    26,    27,    28,    29,    41,    54,    96,
      95,    55,    78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -45
static const yytype_int8 yypact[] =
{
      28,    87,    27,   -45,    -6,   -45,   -45,    87,    18,    36,
     -45,    17,    87,    68,   -45,    36,   -45,    11,    35,   -45,
      69,    71,   -45,    75,    97,    17,    72,    72,    72,    73,
      87,   -45,    76,    35,    86,    19,    88,   -45,   -45,   -45,
      17,   -45,    96,   -45,    19,    89,    12,   -45,   -45,    19,
      12,    19,   -45,    53,    -9,   -45,    12,    77,   -45,    -7,
      12,    12,    63,   -45,   -45,    38,    39,   -45,   -45,   -45,
     -45,   -45,   -45,    12,    12,    12,    12,    12,    12,   -45,
     -45,   101,    63,   -45,   -45,    63,    58,   -45,   -45,    67,
      67,   -45,   -45,   -45,    63,    19,    19,   -45,    98,   -45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -45,   -45,   -45,   -45,   104,    -5,   -45,    33,    32,   -45,
     -42,   -19,   -45,   -45,   -45,   -45,   -45,    74,   -44,   -45,
     -45,   -45,   -45
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -15
static const yytype_int8 yytable[] =
{
      59,    11,    13,    12,    62,    63,    39,    66,    64,    65,
      79,    80,    79,    80,    82,    16,    47,    48,    85,    86,
      16,    57,    16,    47,    48,    13,    81,    10,    84,    19,
      20,    89,    90,    91,    92,    93,    94,     1,    50,    16,
      49,    18,    17,    22,    34,    50,    61,    33,    32,    14,
      15,    98,    99,    51,    67,    68,    69,    22,    79,    80,
      70,    71,    72,    73,    74,    75,    76,    77,   -14,    67,
      68,    69,    22,    87,    88,    70,    71,    72,    73,    74,
      75,    76,    77,    73,    74,    75,    76,    77,    73,    74,
      75,    76,    77,    87,    75,    76,    77,     5,     6,    31,
      15,    42,    43,    35,    36,    38,    37,    44,    40,    45,
      46,    58,    56,    60,    83,    97,    30,     0,    80
};

static const yytype_int8 yycheck[] =
{
      44,     7,     7,     9,    46,    49,    25,    51,    50,    51,
      19,    20,    19,    20,    56,     3,     4,     5,    60,    61,
       3,    40,     3,     4,     5,    30,    35,     0,    35,    12,
      13,    73,    74,    75,    76,    77,    78,     9,    26,     3,
      21,     9,     9,    11,    33,    26,    34,    15,    15,    31,
      32,    95,    96,    34,    16,    17,    18,    25,    19,    20,
      22,    23,    24,    25,    26,    27,    28,    29,    33,    16,
      17,    18,    40,    35,    35,    22,    23,    24,    25,    26,
      27,    28,    29,    25,    26,    27,    28,    29,    25,    26,
      27,    28,    29,    35,    27,    28,    29,    10,    11,    31,
      32,    27,    28,    34,    33,     8,    31,    34,    36,    33,
      24,    15,    24,    24,    37,    14,    12,    -1,    20
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    39,    40,    41,    10,    11,    42,    43,    44,
       0,     7,     9,    43,    31,    32,     3,    45,    46,    12,
      13,    45,    46,    47,    49,    50,    51,    52,    53,    54,
      42,    31,    45,    46,    33,    34,    33,    31,     8,    49,
      36,    55,    55,    55,    34,    33,    24,     4,     5,    21,
      26,    34,    46,    48,    56,    59,    24,    49,    15,    56,
      24,    34,    48,    56,    48,    48,    56,    16,    17,    18,
      22,    23,    24,    25,    26,    27,    28,    29,    60,    19,
      20,    35,    48,    37,    35,    48,    48,    35,    35,    48,
      48,    48,    48,    48,    48,    58,    57,    14,    56,    56
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 119 "yyfx.y"
    {
				(yyval.CH)=0;
				fprintf(yffx, "Program ::= subProg\n");
				fprintf(yffx, "\nCompile successfully!\n");
			;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 126 "yyfx.y"
    {/*BackPatch($3,NXQ);*/
				GEN("Stop",0,0,0);
				fprintf(yffx, "SubProg ::= VarDef Begin StateList End\n");
			;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 132 "yyfx.y"
    {
				(yyval.CH)=0;
				fprintf(yffx, "VarDef ::= VarDef Var VarDefList\n");
			;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 137 "yyfx.y"
    {
				(yyval.CH)=0;
				fprintf(yffx, "VarDef ::= Var VarDefList\n");
			;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 141 "yyfx.y"
    {(yyval.CH)=0;fprintf(yffx, "VarDefList ::= VarDefList VarList\n");;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 142 "yyfx.y"
    {(yyval.CH)=0;fprintf(yffx, "VarDefList ::= VarList\n");;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 145 "yyfx.y"
    {
				FillType((yyvsp[(3) - (3)].NO),(yyvsp[(1) - (3)].First));
				fprintf(yffx, "VarList ::= VarList , Varable\n");
			;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 150 "yyfx.y"
    {
				(yyval.First)=(yyvsp[(1) - (2)].Iv);
				FillType((yyvsp[(2) - (2)].NO),(yyval.First));
				fprintf(yffx, "VarList ::= Type Varable\n");
			;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 156 "yyfx.y"
    {
				FillType((yyvsp[(3) - (6)].NO),(yyvsp[(1) - (6)].First));
				fprintf(yffx, "VarList ::= VarList,Asign_Varable:=Expr\n");
				if(VarList[(yyvsp[(3) - (6)].NO)].type==(yyvsp[(6) - (6)]._Expr).type)
					GEN(":=",(yyvsp[(6) - (6)]._Expr).place,0,(yyvsp[(3) - (6)].NO));
				else if((yyvsp[(6) - (6)]._Expr).type==INTTYPE && VarList[(yyvsp[(3) - (6)].NO)].type==REALTYPE)
				{
					int T=NewTemp();
					GEN("I->R",(yyvsp[(6) - (6)]._Expr).place,0,T);//类型转换
					GEN(":=",T,0,(yyvsp[(3) - (6)].NO));
				}
				else if((yyvsp[(6) - (6)]._Expr).type==REALTYPE && VarList[(yyvsp[(3) - (6)].NO)].type==INTTYPE)
				{
					int T=NewTemp();
					GEN("R->I",(yyvsp[(6) - (6)]._Expr).place,0,T);//类型转换
					GEN(":=",T,0,(yyvsp[(3) - (6)].NO));
				}
			;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 175 "yyfx.y"
    {
				(yyval.First)=(yyvsp[(1) - (5)].Iv);FillType((yyvsp[(2) - (5)].NO),(yyval.First));
				fprintf(yffx, "VarList ::= Type Asign_Varable := Expr\n");
				if(VarList[(yyvsp[(2) - (5)].NO)].type==(yyvsp[(5) - (5)]._Expr).type)
					GEN(":=",(yyvsp[(5) - (5)]._Expr).place,0,(yyvsp[(2) - (5)].NO));
				else if((yyvsp[(5) - (5)]._Expr).type==INTTYPE && VarList[(yyvsp[(2) - (5)].NO)].type==REALTYPE)
				{
					int T=NewTemp();
					GEN("I->R",(yyvsp[(5) - (5)]._Expr).place,0,T);//类型转换
					GEN(":=",T,0,(yyvsp[(2) - (5)].NO));
				}
				else if((yyvsp[(5) - (5)]._Expr).type==REALTYPE && VarList[(yyvsp[(2) - (5)].NO)].type==INTTYPE)
				{
					int T=NewTemp();
					GEN("R->I",(yyvsp[(5) - (5)]._Expr).place,0,T);//类型转换
					GEN(":=",T,0,(yyvsp[(2) - (5)].NO));
				}
			;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 196 "yyfx.y"
    {
			(yyval.Iv)=INTTYPE;/*Type.lv=0*/
			fprintf(yffx, "Type ::= Integer\n");
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 201 "yyfx.y"
    {
			(yyval.Iv)=REALTYPE;/*Type.lv=1*/
			fprintf(yffx, "Type ::= Real\n");
		;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 208 "yyfx.y"
    {(yyval.NO)=(yyvsp[(1) - (1)].NO);fprintf(yffx, "Asign_Varable ::= Varable\n");;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 211 "yyfx.y"
    { 
				(yyval.NO)=Entry(key);/*Varable.NO=VarCount*/
				fprintf(yffx, "Varable ::= Iden\n");
			;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 218 "yyfx.y"
    {
				(yyval._WBD).QUAD=(yyvsp[(1) - (4)].NO);(yyval._WBD).CH=NXQ-1;
				fprintf(yffx, "AsignState ::= Asign_Varable:=Expr\n");
				if(VarList[(yyvsp[(1) - (4)].NO)].type==(yyvsp[(4) - (4)]._Expr).type)
					GEN(":=",(yyvsp[(4) - (4)]._Expr).place,0,(yyvsp[(1) - (4)].NO));
				else if((yyvsp[(4) - (4)]._Expr).type==INTTYPE && VarList[(yyvsp[(1) - (4)].NO)].type==REALTYPE)
				{
					int T=NewTemp();
					GEN("I->R",(yyvsp[(4) - (4)]._Expr).place,0,T);//类型转换
					GEN(":=",T,0,(yyvsp[(1) - (4)].NO));
				}
				else if((yyvsp[(4) - (4)]._Expr).type==REALTYPE && VarList[(yyvsp[(1) - (4)].NO)].type==INTTYPE)
				{
					int T=NewTemp();
					GEN("R->I",(yyvsp[(4) - (4)]._Expr).place,0,T);//类型转换
					GEN(":=",T,0,(yyvsp[(1) - (4)].NO));
				}
			;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 239 "yyfx.y"
    {
			fprintf(yffx, "Expr ::= Expr+Expr\n");
			int T=NewTemp();
			if((yyvsp[(1) - (3)]._Expr).type== INTTYPE && (yyvsp[(3) - (3)]._Expr).type==INTTYPE)
			{
			GEN("Int+",(yyvsp[(1) - (3)]._Expr).place,(yyvsp[(3) - (3)]._Expr).place,T);
			VarList[T].type=(yyval._Expr).type=INTTYPE;
			}
			else if((yyvsp[(1) - (3)]._Expr).type== REALTYPE && (yyvsp[(3) - (3)]._Expr).type==REALTYPE)
			{
			GEN("Real+",(yyvsp[(1) - (3)]._Expr).place,(yyvsp[(3) - (3)]._Expr).place,T);
			VarList[T].type=(yyval._Expr).type=REALTYPE;
			}
			else if((yyvsp[(1) - (3)]._Expr).type== INTTYPE)
			{
			int U=NewTemp();
			GEN("I->R",(yyvsp[(1) - (3)]._Expr).place,0,U);//先将integer转换成real型
			GEN("Real+",U,(yyvsp[(3) - (3)]._Expr).place,T);
			VarList[T].type=(yyval._Expr).type=REALTYPE;
			}
			else
			{
			int U=NewTemp();
			GEN("I->R",(yyvsp[(3) - (3)]._Expr).place,0,U);
			GEN("Real+",(yyvsp[(1) - (3)]._Expr).place,U,T);
			VarList[T].type=(yyval._Expr).type=REALTYPE;
			}
			(yyval._Expr).place=T;
		;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 269 "yyfx.y"
    {
		fprintf(yffx, "Expr ::= Expr-Expr\n");
		int T=NewTemp();
		if((yyvsp[(1) - (3)]._Expr).type== INTTYPE && (yyvsp[(3) - (3)]._Expr).type==INTTYPE)
		{
		GEN("Int-",(yyvsp[(1) - (3)]._Expr).place,(yyvsp[(3) - (3)]._Expr).place,T);
		VarList[T].type=(yyval._Expr).type=INTTYPE;
		}
		else if((yyvsp[(1) - (3)]._Expr).type== REALTYPE && (yyvsp[(3) - (3)]._Expr).type==REALTYPE)
		{
		GEN("Real-",(yyvsp[(1) - (3)]._Expr).place,(yyvsp[(3) - (3)]._Expr).place,T);
		VarList[T].type=(yyval._Expr).type=REALTYPE;
		}
		else if((yyvsp[(1) - (3)]._Expr).type== INTTYPE)
		{
		int U=NewTemp();
		GEN("I->R",(yyvsp[(1) - (3)]._Expr).place,0,U);
		GEN("Real-",U,(yyvsp[(3) - (3)]._Expr).place,T);
		VarList[T].type=(yyval._Expr).type=REALTYPE;
		}
		else
		{
		int U=NewTemp();
		GEN("I->R",(yyvsp[(3) - (3)]._Expr).place,0,U);
		GEN("R-",(yyvsp[(1) - (3)]._Expr).place,U,T);
		VarList[T].type=(yyval._Expr).type=REALTYPE;
		}
		(yyval._Expr).place=T;
	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 300 "yyfx.y"
    {
		fprintf(yffx, "Expr ::= Expr*Expr\n");
		int T=NewTemp();
		if((yyvsp[(1) - (3)]._Expr).type== INTTYPE && (yyvsp[(3) - (3)]._Expr).type==INTTYPE)
		{
			GEN("Int*",(yyvsp[(1) - (3)]._Expr).place,(yyvsp[(3) - (3)]._Expr).place,T);
			VarList[T].type=(yyval._Expr).type=INTTYPE;
		}
		else if((yyvsp[(1) - (3)]._Expr).type== REALTYPE && (yyvsp[(3) - (3)]._Expr).type==REALTYPE)
		{
			GEN("Real*",(yyvsp[(1) - (3)]._Expr).place,(yyvsp[(3) - (3)]._Expr).place,T);
			VarList[T].type=(yyval._Expr).type=REALTYPE;
		}
		else if((yyvsp[(1) - (3)]._Expr).type== INTTYPE)
		{
			int U=NewTemp();
			GEN("I->R",(yyvsp[(1) - (3)]._Expr).place,0,U);
			GEN("Real*",U,(yyvsp[(3) - (3)]._Expr).place,T);
			VarList[T].type=(yyval._Expr).type=REALTYPE;
		}
		else
		{
			int U=NewTemp();
			GEN("I->R",(yyvsp[(3) - (3)]._Expr).place,0,U);
			GEN("Real*",(yyvsp[(1) - (3)]._Expr).place,U,T);
			VarList[T].type=(yyval._Expr).type=REALTYPE;
		}
		(yyval._Expr).place=T;
	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 330 "yyfx.y"
    {
		fprintf(yffx, "Expr ::= Expr/Expr\n");
		int T=NewTemp();
		if((yyvsp[(1) - (3)]._Expr).type== INTTYPE && (yyvsp[(3) - (3)]._Expr).type==INTTYPE){
			GEN("Int/",(yyvsp[(1) - (3)]._Expr).place,(yyvsp[(3) - (3)]._Expr).place,T);
			VarList[T].type=(yyval._Expr).type=INTTYPE;
		}
		else if((yyvsp[(1) - (3)]._Expr).type== REALTYPE && (yyvsp[(3) - (3)]._Expr).type==REALTYPE)
		{
			GEN("Real/",(yyvsp[(1) - (3)]._Expr).place,(yyvsp[(3) - (3)]._Expr).place,T);
			VarList[T].type=(yyval._Expr).type=REALTYPE;
		}
		else if((yyvsp[(1) - (3)]._Expr).type== INTTYPE)
		{
			int U=NewTemp();
			GEN("I->R",(yyvsp[(1) - (3)]._Expr).place,0,U);
			GEN("Real/",U,(yyvsp[(3) - (3)]._Expr).place,T);
			VarList[T].type=(yyval._Expr).type=REALTYPE;
		}
		else{
			int U=NewTemp();
			GEN("I->R",(yyvsp[(3) - (3)]._Expr).place,0,U);
			GEN("Real/",(yyvsp[(1) - (3)]._Expr).place,U,T);
			VarList[T].type=(yyval._Expr).type=REALTYPE;
		}
		(yyval._Expr).place=T;
	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 358 "yyfx.y"
    {
		fprintf(yffx, "Expr ::= Expr%%Expr\n");
		int T=NewTemp();
		if((yyvsp[(1) - (3)]._Expr).type== INTTYPE && (yyvsp[(3) - (3)]._Expr).type==INTTYPE)
		{
			GEN("Int%",(yyvsp[(1) - (3)]._Expr).place,(yyvsp[(3) - (3)]._Expr).place,T);
			VarList[T].type=(yyval._Expr).type=INTTYPE;
			(yyval._Expr).place=T;
		}
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 369 "yyfx.y"
    {
		fprintf(yffx, "Expr ::= (Expr)\n");
		(yyval._Expr)=(yyvsp[(2) - (3)]._Expr);
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 374 "yyfx.y"
    {
		fprintf(yffx, "Expr ::= -Expr\n");
		int T=NewTemp();
		(yyval._Expr)=(yyvsp[(2) - (2)]._Expr);
		GEN("Minus",(yyvsp[(2) - (2)]._Expr).place,0,T);
		(yyval._Expr).place=T;VarList[T].type=VarList[(yyvsp[(2) - (2)]._Expr).place].type;
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 382 "yyfx.y"
    {
		fprintf(yffx, "Expr ::= Varable\n");
		(yyval._Expr).place=(yyvsp[(1) - (1)].NO);
		(yyval._Expr).type=VarList[(yyvsp[(1) - (1)].NO)].type;

	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 389 "yyfx.y"
    { 
		fprintf(yffx, "Expr ::= Const\n");
		(yyval._Expr)=(yyvsp[(1) - (1)]._Expr);
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 398 "yyfx.y"
    {
				fprintf(yffx, "StateList ::= Statement\n");
				(yyval.CH)=(yyvsp[(1) - (1)].CH);BackPatch((yyvsp[(1) - (1)].CH),NXQ);
			;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 403 "yyfx.y"
    {
				fprintf(yffx, "StateList ::= Statement StateList\n");
				(yyval.CH)=(yyvsp[(1) - (2)].CH);BackPatch((yyvsp[(1) - (2)].CH),NXQ);
			;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 409 "yyfx.y"
    {
				(yyval.CH)=0;
				fprintf(yffx, "Statement ::= AsignState;\n");
			;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 414 "yyfx.y"
    {
			fprintf(yffx, "Statement ::= I_T_E ComplexState;\n");
			(yyval.CH)=Merge((yyvsp[(1) - (2)].CH),(yyvsp[(2) - (2)].CH));
		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 419 "yyfx.y"
    { //循环语句
			fprintf(yffx, "Statement ::= Wd ComplexState;\n");
			GEN("j",0,0,(yyvsp[(1) - (2)]._WBD).QUAD);
			/*printf("\n\nQUAD%d\n",$1.QUAD;)*/
			BackPatch((yyvsp[(2) - (2)].CH),(yyvsp[(1) - (2)]._WBD).QUAD);
			(yyval.CH)=(yyvsp[(1) - (2)]._WBD).CH;
		;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 430 "yyfx.y"
    {
				fprintf(yffx, "I_T_E ::= I_T ComplexState Else\n");
				int q=NXQ;GEN("j",0,0,0);BackPatch((yyvsp[(1) - (3)].CH),NXQ);(yyval.CH)=Merge((yyvsp[(2) - (3)].CH),q);
			;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 436 "yyfx.y"
    {
			fprintf(yffx, "I_T ::= If ( BoolExpr ) Then\n");
			BackPatch((yyvsp[(3) - (5)]._BExpr).TC,NXQ);(yyval.CH)=(yyvsp[(3) - (5)]._BExpr).FC;
		;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 441 "yyfx.y"
    {
			fprintf(yffx, "I_T ::= If ( BoolExpr )\n");
			BackPatch((yyvsp[(3) - (4)]._BExpr).TC,NXQ);(yyval.CH)=(yyvsp[(3) - (4)]._BExpr).FC;
		;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 447 "yyfx.y"
    {
			fprintf(yffx, "Wd ::= W (BoolExpr) \n");
			BackPatch((yyvsp[(3) - (4)]._BExpr).TC,NXQ);(yyval._WBD).QUAD=(yyvsp[(1) - (4)].CH);(yyval._WBD).CH=(yyvsp[(3) - (4)]._BExpr).FC;
		;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 452 "yyfx.y"
    {(yyval.CH)=NXQ;fprintf(yffx, "W ::= While\n");;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 457 "yyfx.y"
    {	
					fprintf(yffx, "ComplexState ::= [StateList] \n");
					(yyval.CH)=(yyvsp[(2) - (3)].CH);	
				;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 464 "yyfx.y"
    {
				fprintf(yffx, "BoolExpr ::= Expr RelationOp Expr\n");
				(yyval._BExpr).TC=NXQ;(yyval._BExpr).FC=NXQ+1;
				GEN((yyvsp[(2) - (3)]._Rop),(yyvsp[(1) - (3)]._Expr).place,(yyvsp[(3) - (3)]._Expr).place,0);//真链第NXQ个四元式，等待回填
				GEN("j",0,0,0);                       //假链四元式，等待回填
			;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 470 "yyfx.y"
    {BackPatch((yyvsp[(1) - (2)]._BExpr).TC,NXQ);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 471 "yyfx.y"
    {
			fprintf(yffx, "BoolExpr ::= BoolExpr & BoolExpr \n");
			(yyval._BExpr).TC=(yyvsp[(4) - (4)]._BExpr).TC;(yyval._BExpr).FC=Merge((yyvsp[(1) - (4)]._BExpr).FC,(yyvsp[(4) - (4)]._BExpr).FC);
		;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 475 "yyfx.y"
    {BackPatch((yyvsp[(1) - (2)]._BExpr).FC,NXQ);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 476 "yyfx.y"
    {
			fprintf(yffx, "BoolExpr ::= BoolExpr | BoolExpr \n");
			(yyval._BExpr).FC=(yyvsp[(4) - (4)]._BExpr).FC;(yyval._BExpr).TC=Merge((yyvsp[(1) - (4)]._BExpr).TC,(yyvsp[(4) - (4)]._BExpr).TC);
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 483 "yyfx.y"
    {
			fprintf(yffx, "BoolExpr ::= !BoolExpr \n");
			(yyval._BExpr).TC=(yyvsp[(2) - (2)]._BExpr).FC;(yyval._BExpr).FC=(yyvsp[(2) - (2)]._BExpr).TC;
		;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 488 "yyfx.y"
    {
			fprintf(yffx, "BoolExpr ::= (BoolExpr)\n");
			(yyval._BExpr)=(yyvsp[(2) - (3)]._BExpr);
		;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 494 "yyfx.y"
    { 
			fprintf(yffx, "Const ::= IntNo\n");
			int i=Entry(key);
			(yyval._Expr).type=VarList[i].type=INTTYPE;
			(yyval._Expr).place=i;
		;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 501 "yyfx.y"
    { 
			fprintf(yffx, "Const ::= RealNo\n");
			int i=Entry(key);
			(yyval._Expr).type=VarList[i].type=REALTYPE;
			(yyval._Expr).place=i;
		;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 508 "yyfx.y"
    {strcpy((yyval._Rop),"j<");fprintf(yffx, "RelationOp ::= < \n");;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 509 "yyfx.y"
    {strcpy((yyval._Rop),"j>");fprintf(yffx, "RelationOp ::= > \n");;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 510 "yyfx.y"
    {strcpy((yyval._Rop),"j=");fprintf(yffx, "RelationOp ::= = \n");;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 511 "yyfx.y"
    {strcpy((yyval._Rop),"j>=");fprintf(yffx, "RelationOp ::= >= \n");;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 512 "yyfx.y"
    {strcpy((yyval._Rop),"j!=");fprintf(yffx, "RelationOp ::= != \n");;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 513 "yyfx.y"
    {strcpy((yyval._Rop),"j<=");fprintf(yffx, "RelationOp ::= <= \n");;}
    break;



/* Line 1455 of yacc.c  */
#line 2130 "yyfx.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 515 "yyfx.y"


void OutputQ(void)
{
	int i;
	fprintf(yyfx,"\nQuarterList output:\n");
	for(i=0;i<NXQ;i++)
	{
		fprintf(yyfx,"%4d ( %8s, ",i,QuaterList[i].op);
		if(QuaterList[i].arg1)
			fprintf(yyfx,"%6s, ",VarList[QuaterList[i].arg1].name);
		else 
			fprintf(yyfx,"      , ");
		if(QuaterList[i].arg2)
			fprintf(yyfx,"%6s, ",VarList[QuaterList[i].arg2].name);
		else 
			fprintf(yyfx,"      , ");
		if((QuaterList[i].op[0]=='j')||(QuaterList[i].op[0]=='S')) 
			fprintf(yyfx,"%6d )\n",QuaterList[i].result);
		else if(QuaterList[i].result)
			fprintf(yyfx,"%6s )\n",VarList[QuaterList[i].result].name);
		else 
			fprintf(yyfx,"-\t )\n");
	}
	return;
}

int yyerror(char *errstr)
{
	fprintf(yffx,"(%d,%d):%s!\n",row_num, col_num,errstr);
	// fprintf(yffx, "Error occurred in rule: %s\n", yytext);
	return 0;
}

int Entry(char *name)
{
	int i;
	for(i=1;i<=VarCount;i++) 
		if(!strcmp(name,VarList[i].name)) 
					return i;
	if(++VarCount>MAXMEMBER) 
	{
			fprintf(yffx,"Too many Variables!\n");exit(-1);
	}
	strcpy(VarList[VarCount].name,name);
	return VarCount;
}

int FillType(int first,int type)
{ 
    int i;
    for(i=first;i<=VarCount;i++)
		VarList[i].type=type;
    return i-1;
}

int Merge(int p,int q)
{
   int r;
   if(!q) 
        return p;
   else
   {
       r=q;
       while(QuaterList[r].result)
        r=QuaterList[r].result;
       QuaterList[r].result=p;
   }
   return q;
}

void BackPatch(int p,int t)
{
     int q=p;
     while(q)
     { 
           int q1=QuaterList[q].result;
           QuaterList[q].result=t;
           q=q1;
     } 
     return;
}

int GEN(char* op,int a1,int a2,int re)
{
	strcpy(QuaterList[NXQ].op,op);
	QuaterList[NXQ].arg1=a1;
	QuaterList[NXQ].arg2=a2;
	QuaterList[NXQ].result=re;
	NXQ++;
	return NXQ;
}

int NewTemp()
{
	static int no=0;
	char Tname[10];
	sprintf(Tname,"T%o",no++);
	return Entry(Tname);
}


int main(int argc, char *argv[])
{
	yyfx = fopen("D:\\Code\\Cpp\\compiler\\module\\yyfx.txt", "w+");
	yffx = fopen("D:\\Code\\Cpp\\compiler\\module\\yffx.txt", "w+");
	yyparse();
	OutputQ();
	getchar();
	return 1;
 }
