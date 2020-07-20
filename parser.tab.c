/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
#define YYBISON_VERSION "3.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser.y"

#  include <stdio.h>
#  include <stdlib.h>
#  include <vips/vips.h>
#  include "utils.h"

#line 77 "parser.tab.c"

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
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    NAME = 259,
    PATH = 260,
    FUNC = 261,
<<<<<<< HEAD
    EOL = 262,
    IF = 263,
    THEN = 264,
    ELSE = 265,
    WHILE = 266,
    DO = 267,
<<<<<<< HEAD
    LET = 268,
<<<<<<< HEAD
    CMP = 269,
    UMINUS = 270
=======
    NUM = 269,
    IMG = 270,
    CMP = 271,
    UMINUS = 272
>>>>>>> master
=======
    DEF = 268,
    NUM = 269,
    IMG = 270,
    INFO = 271,
    CMP = 272,
    UMINUS = 273
>>>>>>> master
=======
    IF = 262,
    THEN = 263,
    ELSE = 264,
    WHILE = 265,
    DO = 266,
    DEF = 267,
    NUM = 268,
    IMG = 269,
    INFO = 270,
    CMP = 271,
    UMINUS = 272
>>>>>>> master
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 10 "parser.y"

  struct ast *a;
  double d;
  char * str;
  struct symbol *s;		/* which symbol */
  struct symlist *sl;
  int fn;			/* which function */

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#line 143 "parser.tab.c"
=======
#line 147 "parser.tab.c"
>>>>>>> master
=======
#line 148 "parser.tab.c"
>>>>>>> master
=======
#line 147 "parser.tab.c"
>>>>>>> master

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



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
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#define YYLAST   116

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  29
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  64

#define YYUNDEFTOK  2
#define YYMAXUTOK   270
=======
#define YYLAST   141
=======
#define YYLAST   146
>>>>>>> master
=======
#define YYLAST   138
>>>>>>> master

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  31
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  69

#define YYUNDEFTOK  2
<<<<<<< HEAD
<<<<<<< HEAD
#define YYMAXUTOK   272
>>>>>>> master
=======
#define YYMAXUTOK   273
>>>>>>> master
=======
#define YYMAXUTOK   272
>>>>>>> master

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      25,    26,    20,    18,    27,    19,     2,    21,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    24,
       2,    17,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
      23,    24,    18,    16,    25,    17,     2,    19,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
       2,    15,     2,     2,     2,     2,     2,     2,     2,     2,
=======
      25,    26,    20,    18,    27,    19,     2,    21,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    24,
       2,    17,     2,     2,     2,     2,     2,     2,     2,     2,
>>>>>>> master
=======
      26,    27,    21,    19,    28,    20,     2,    22,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
       2,    18,     2,     2,     2,     2,     2,     2,     2,     2,
>>>>>>> master
=======
>>>>>>> master
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
<<<<<<< HEAD
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
<<<<<<< HEAD
<<<<<<< HEAD
       2,     2,     2,     2,    20,     2,     2,     2,     2,     2,
=======
       2,     2,     2,     2,    22,     2,     2,     2,     2,     2,
>>>>>>> master
=======
       2,     2,     2,     2,    23,     2,     2,     2,     2,     2,
>>>>>>> master
=======
       2,     2,     2,     2,    22,     2,     2,     2,     2,     2,
>>>>>>> master
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
      21
=======
      15,    16,    23
>>>>>>> master
=======
      15,    16,    17,    24
>>>>>>> master
=======
      15,    16,    23
>>>>>>> master
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
       0,    40,    40,    41,    42,    43,    46,    47,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    70,    71,    73,    74,    77,    78,    83,    87
=======
       0,    42,    42,    43,    44,    45,    48,    49,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
<<<<<<< HEAD
      68,    69,    70,    73,    74,    76,    77,    80,    81,    86,
      90
>>>>>>> master
=======
      68,    69,    70,    71,    74,    75,    77,    78,    81,    82,
      87,    91
>>>>>>> master
=======
       0,    41,    41,    42,    43,    44,    47,    48,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    73,    74,    76,    77,    80,    81,
      86,    90
>>>>>>> master
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
<<<<<<< HEAD
  "$end", "error", "$undefined", "NUMBER", "NAME", "PATH", "FUNC", "EOL",
<<<<<<< HEAD
<<<<<<< HEAD
  "IF", "THEN", "ELSE", "WHILE", "DO", "LET", "CMP", "'='", "'+'", "'-'",
  "'*'", "'/'", "'|'", "UMINUS", "';'", "'('", "')'", "','", "$accept",
  "stmt", "list", "exp", "explist", "symlist", "calclist", YY_NULLPTR
=======
  "IF", "THEN", "ELSE", "WHILE", "DO", "LET", "NUM", "IMG", "CMP", "'='",
  "'+'", "'-'", "'*'", "'/'", "'|'", "UMINUS", "';'", "'('", "')'", "','",
  "$accept", "stmt", "list", "exp", "explist", "symlist", "calclist", YY_NULLPTR
>>>>>>> master
=======
  "IF", "THEN", "ELSE", "WHILE", "DO", "DEF", "NUM", "IMG", "INFO", "CMP",
  "'='", "'+'", "'-'", "'*'", "'/'", "'|'", "UMINUS", "';'", "'('", "')'",
  "','", "$accept", "stmt", "list", "exp", "explist", "symlist",
  "calclist", YY_NULLPTR
>>>>>>> master
=======
  "$end", "error", "$undefined", "NUMBER", "NAME", "PATH", "FUNC", "IF",
  "THEN", "ELSE", "WHILE", "DO", "DEF", "NUM", "IMG", "INFO", "CMP", "'='",
  "'+'", "'-'", "'*'", "'/'", "'|'", "UMINUS", "';'", "'('", "')'", "','",
  "'\\n'", "$accept", "stmt", "list", "exp", "explist", "symlist",
  "program", YY_NULLPTR
>>>>>>> master
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
     265,   266,   267,   268,   269,    61,    43,    45,    42,    47,
     124,   270,    59,    40,    41,    44
};
# endif

#define YYPACT_NINF -31

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-31)))
=======
     265,   266,   267,   268,   269,   270,   271,    61,    43,    45,
      42,    47,   124,   272,    59,    40,    41,    44
=======
     265,   266,   267,   268,   269,   270,   271,   272,    61,    43,
      45,    42,    47,   124,   273,    59,    40,    41,    44
>>>>>>> master
=======
     265,   266,   267,   268,   269,   270,   271,    61,    43,    45,
      42,    47,   124,   272,    59,    40,    41,    44,    10
>>>>>>> master
};
# endif

#define YYPACT_NINF -32

#define yypact_value_is_default(Yystate) \
<<<<<<< HEAD
<<<<<<< HEAD
  (!!((Yystate) == (-32)))
>>>>>>> master
=======
  (!!((Yystate) == (-33)))
>>>>>>> master
=======
  (!!((Yystate) == (-32)))
>>>>>>> master

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
     -31,    35,   -31,    20,   -31,    -7,   -31,     7,     9,     9,
       2,     9,     9,     9,    26,    87,   -31,     9,     9,     9,
      66,    81,    11,   -31,   -31,    72,   -31,     9,     9,     9,
       9,     9,    97,    52,    18,    21,    56,    56,    40,   -31,
      93,    -1,    -1,   -31,   -31,     9,   -31,   -31,    25,    39,
     -31,    28,    27,   -31,    56,    56,    40,    41,   -31,   -31,
     -31,    56,    43,   -31
=======
     -32,    39,   -32,     3,   -32,   -12,   -32,   -11,    85,    85,
      11,    23,    26,    85,    85,    85,    25,   110,   -32,    85,
      85,     0,   104,     9,    19,    85,   -32,   -32,    93,   -32,
      85,    85,    85,    85,    85,    76,    12,    20,    62,    62,
      33,    85,   110,   -32,   116,   -17,   -17,   -32,   -32,    85,
     -32,   -32,    24,    41,   -32,    22,    29,   120,   -32,    62,
      62,    33,    40,   -32,   -32,   -32,    62,    49,   -32
>>>>>>> master
=======
     -33,    41,   -33,    -2,   -33,   -16,   -33,   -15,    89,    89,
      10,    11,    12,    19,    89,    89,    89,    24,     0,   -33,
      89,    89,    80,   109,     7,    16,    89,   -33,   -33,   -33,
     115,   -33,    89,    89,    89,    89,    89,    97,    21,    23,
      65,    65,    47,    89,     0,   -33,   124,   -18,   -18,   -33,
     -33,    89,   -33,   -33,    28,    48,   -33,    31,    33,    18,
     -33,    65,    65,    47,    44,   -33,   -33,   -33,    65,    56,
     -33
>>>>>>> master
=======
     -32,    40,   -32,   -23,   -32,   -15,   -32,   -14,    86,    86,
      10,    11,    12,    28,    86,    86,    86,   -32,   111,   -32,
      86,    86,    94,   105,     8,    18,    86,   -32,   -32,   -32,
      77,    86,    86,    86,    86,    86,     1,    13,    22,    63,
      63,    33,    86,   111,   -32,   117,   -17,   -17,   -32,   -32,
      86,   -32,   -32,    14,    42,   -32,    29,    23,    99,   -32,
      63,    63,    33,    41,   -32,   -32,   -32,    63,   -32
>>>>>>> master
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
      26,     0,     1,     0,    16,    18,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     5,    29,     0,     0,     0,
       0,     0,     0,    15,    13,     0,    27,     0,     0,     0,
       0,     0,    20,    22,     0,     0,     6,     6,     0,    14,
       8,     9,    10,    11,    12,     0,    21,    17,     0,     2,
       4,    24,     0,    23,     6,     6,     0,     0,     7,     3,
      25,     6,     0,    28
=======
      27,     0,     1,     0,    16,    19,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,    30,     0,
       0,     0,     0,     0,     0,     0,    15,    13,     0,    28,
       0,     0,     0,     0,     0,    23,     0,     0,     6,     6,
       0,     0,    21,    14,     8,     9,    10,    11,    12,     0,
      22,    18,     0,     2,     4,    25,     0,    20,    24,     6,
       6,     0,     0,     7,     3,    26,     6,     0,    29
>>>>>>> master
=======
      28,     0,     1,     0,    16,    19,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     5,    31,
       0,     0,     0,     0,     0,     0,     0,    22,    15,    13,
<<<<<<< HEAD
       0,    29,     0,     0,     0,     0,     0,    24,     0,     0,
       6,     6,     0,     0,    21,    14,     8,     9,    10,    11,
      12,     0,    23,    18,     0,     2,     4,    26,     0,    20,
      25,     6,     6,     0,     0,     7,     3,    27,     6,     0,
      30
>>>>>>> master
=======
       0,     0,     0,     0,     0,     0,    24,     0,     0,     6,
       6,     0,     0,    21,    14,     8,     9,    10,    11,    12,
       0,    23,    18,     0,     2,     4,    26,     0,    20,    25,
       6,     6,     0,     0,     7,     3,    27,     6,    30
>>>>>>> master
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
     -31,    53,   -30,    -8,   -17,     1,   -31
=======
     -32,    58,   -31,    -8,   -18,    -1,   -32
>>>>>>> master
=======
     -33,    64,   -32,    -8,   -19,     3,   -33
>>>>>>> master
=======
     -32,    56,   -31,    -8,   -19,    -2,   -32
>>>>>>> master
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
      -1,    48,    49,    15,    34,    52,     1
=======
      -1,    52,    53,    17,    36,    56,     1
>>>>>>> master
=======
      -1,    54,    55,    18,    38,    58,     1
>>>>>>> master
=======
      -1,    53,    54,    18,    37,    57,     1
>>>>>>> master
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
      20,    21,    35,    23,    24,    25,    22,    50,    17,    32,
      33,    33,     4,     5,     6,     7,    18,    30,    31,    40,
      41,    42,    43,    44,    58,    59,    11,    16,    53,    12,
      19,    62,    13,    26,    38,     2,     3,    33,     4,     5,
       6,     7,    46,     8,    51,    47,     9,    54,    10,    55,
      63,    57,    11,    56,    14,    12,    61,    60,    13,     4,
       5,     6,     7,     0,     8,     0,    27,     9,    28,    29,
      30,    31,     0,    11,     0,    36,    12,    45,     0,    13,
      27,     0,    28,    29,    30,    31,    27,     0,    28,    29,
      30,    31,     0,    37,     0,    27,    39,    28,    29,    30,
      31,    27,     0,    28,    29,    30,    31,    -1,     0,    28,
      29,    30,    31,    28,    29,    30,    31
=======
      21,    22,    37,    33,    34,    26,    27,    28,    54,    38,
      18,    35,    35,    19,    20,    23,    30,    42,    31,    32,
      33,    34,    44,    45,    46,    47,    48,    24,    63,    64,
      25,    58,    29,    57,    40,    67,    41,    55,    50,     2,
       3,    35,     4,     5,     6,     7,    51,     8,    59,    61,
       9,    60,    10,    11,    12,    62,    68,    66,    13,    16,
      65,    14,     0,     0,    15,     4,     5,     6,     7,     0,
       8,     0,     0,     9,     0,     0,    11,    12,     0,     0,
       0,    13,     0,     0,    14,     0,     0,    15,     4,     5,
       6,     7,    30,     0,    31,    32,    33,    34,     0,    11,
      12,     0,     0,    49,    13,     0,     0,    14,     0,    30,
      15,    31,    32,    33,    34,     0,    39,     0,     0,    43,
      30,     0,    31,    32,    33,    34,    30,     0,    31,    32,
      33,    34,    -1,     0,    31,    32,    33,    34,    31,    32,
      33,    34
>>>>>>> master
=======
      22,    23,    39,    35,    36,    19,    28,    29,    30,    56,
      20,    21,    37,    37,    24,    25,    26,    32,    44,    33,
      34,    35,    36,    27,    46,    47,    48,    49,    50,    65,
      66,    31,    60,    42,    43,    59,    69,    33,    34,    35,
      36,     2,     3,    37,     4,     5,     6,     7,    52,     8,
      53,    57,     9,    61,    10,    11,    12,    13,    62,    63,
      64,    14,    68,    70,    15,    17,    67,    16,     4,     5,
       6,     7,     0,     8,     0,     0,     9,     0,     0,    11,
      12,    13,     0,     0,     0,    14,     0,     0,    15,    40,
       0,    16,     4,     5,     6,     7,     0,    32,     0,    33,
      34,    35,    36,    11,    12,    13,     0,     0,     0,    14,
       0,     0,    15,     0,    32,    16,    33,    34,    35,    36,
       0,    41,     0,     0,     0,    51,    32,     0,    33,    34,
      35,    36,    32,     0,    33,    34,    35,    36,     0,     0,
       0,    -1,    45,    33,    34,    35,    36
>>>>>>> master
=======
      22,    23,    38,    34,    35,    19,    28,    29,    30,    55,
      20,    21,    36,    36,    24,    25,    26,    31,    43,    32,
      33,    34,    35,    45,    46,    47,    48,    49,    50,    64,
      65,    59,    27,    41,    58,    42,    68,    56,    60,    51,
       2,     3,    36,     4,     5,     6,     7,     8,    52,    63,
       9,    61,    10,    11,    12,    13,    62,    17,    67,    14,
      66,     0,    15,     0,     0,    16,     4,     5,     6,     7,
       8,     0,     0,     9,     0,     0,    11,    12,    13,     0,
       0,     0,    14,     0,     0,    15,     0,     0,    16,     4,
       5,     6,     7,    31,     0,    32,    33,    34,    35,    11,
      12,    13,    39,    44,     0,    14,     0,     0,    15,     0,
      31,    16,    32,    33,    34,    35,    40,    32,    33,    34,
      35,    31,     0,    32,    33,    34,    35,    31,     0,    32,
      33,    34,    35,    -1,     0,    32,    33,    34,    35
>>>>>>> master
};

static const yytype_int8 yycheck[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
       8,     9,    19,    11,    12,    13,     4,    37,    15,    17,
      18,    19,     3,     4,     5,     6,    23,    18,    19,    27,
      28,    29,    30,    31,    54,    55,    17,     7,    45,    20,
      23,    61,    23,     7,    23,     0,     1,    45,     3,     4,
       5,     6,    24,     8,     4,    24,    11,    22,    13,    10,
       7,    24,    17,    25,     1,    20,    15,    56,    23,     3,
       4,     5,     6,    -1,     8,    -1,    14,    11,    16,    17,
      18,    19,    -1,    17,    -1,     9,    20,    25,    -1,    23,
      14,    -1,    16,    17,    18,    19,    14,    -1,    16,    17,
      18,    19,    -1,    12,    -1,    14,    24,    16,    17,    18,
      19,    14,    -1,    16,    17,    18,    19,    14,    -1,    16,
      17,    18,    19,    16,    17,    18,    19
=======
       8,     9,    20,    20,    21,    13,    14,    15,    39,     9,
       7,    19,    20,    25,    25,     4,    16,    25,    18,    19,
      20,    21,    30,    31,    32,    33,    34,     4,    59,    60,
       4,    49,     7,    41,    25,    66,    17,     4,    26,     0,
       1,    49,     3,     4,     5,     6,    26,     8,    24,    27,
      11,    10,    13,    14,    15,    26,     7,    17,    19,     1,
      61,    22,    -1,    -1,    25,     3,     4,     5,     6,    -1,
       8,    -1,    -1,    11,    -1,    -1,    14,    15,    -1,    -1,
      -1,    19,    -1,    -1,    22,    -1,    -1,    25,     3,     4,
       5,     6,    16,    -1,    18,    19,    20,    21,    -1,    14,
      15,    -1,    -1,    27,    19,    -1,    -1,    22,    -1,    16,
      25,    18,    19,    20,    21,    -1,    12,    -1,    -1,    26,
      16,    -1,    18,    19,    20,    21,    16,    -1,    18,    19,
      20,    21,    16,    -1,    18,    19,    20,    21,    18,    19,
      20,    21
>>>>>>> master
=======
       8,     9,    21,    21,    22,     7,    14,    15,    16,    41,
      26,    26,    20,    21,     4,     4,     4,    17,    26,    19,
      20,    21,    22,     4,    32,    33,    34,    35,    36,    61,
      62,     7,    51,    26,    18,    43,    68,    19,    20,    21,
      22,     0,     1,    51,     3,     4,     5,     6,    27,     8,
      27,     4,    11,    25,    13,    14,    15,    16,    10,    28,
      27,    20,    18,     7,    23,     1,    63,    26,     3,     4,
       5,     6,    -1,     8,    -1,    -1,    11,    -1,    -1,    14,
      15,    16,    -1,    -1,    -1,    20,    -1,    -1,    23,     9,
      -1,    26,     3,     4,     5,     6,    -1,    17,    -1,    19,
      20,    21,    22,    14,    15,    16,    -1,    -1,    -1,    20,
      -1,    -1,    23,    -1,    17,    26,    19,    20,    21,    22,
      -1,    12,    -1,    -1,    -1,    28,    17,    -1,    19,    20,
      21,    22,    17,    -1,    19,    20,    21,    22,    -1,    -1,
      -1,    17,    27,    19,    20,    21,    22
>>>>>>> master
=======
       8,     9,    21,    20,    21,    28,    14,    15,    16,    40,
      25,    25,    20,    21,     4,     4,     4,    16,    26,    18,
      19,    20,    21,    31,    32,    33,    34,    35,    27,    60,
      61,    50,     4,    25,    42,    17,    67,     4,    24,    26,
       0,     1,    50,     3,     4,     5,     6,     7,    26,    26,
      10,     9,    12,    13,    14,    15,    27,     1,    17,    19,
      62,    -1,    22,    -1,    -1,    25,     3,     4,     5,     6,
       7,    -1,    -1,    10,    -1,    -1,    13,    14,    15,    -1,
      -1,    -1,    19,    -1,    -1,    22,    -1,    -1,    25,     3,
       4,     5,     6,    16,    -1,    18,    19,    20,    21,    13,
      14,    15,     8,    26,    -1,    19,    -1,    -1,    22,    -1,
      16,    25,    18,    19,    20,    21,    11,    18,    19,    20,
      21,    16,    -1,    18,    19,    20,    21,    16,    -1,    18,
      19,    20,    21,    16,    -1,    18,    19,    20,    21
>>>>>>> master
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
       0,    32,     0,     1,     3,     4,     5,     6,     8,    11,
      13,    17,    20,    23,    27,    29,     7,    15,    23,    23,
      29,    29,     4,    29,    29,    29,     7,    14,    16,    17,
      18,    19,    29,    29,    30,    30,     9,    12,    23,    24,
      29,    29,    29,    29,    29,    25,    24,    24,    27,    28,
      28,     4,    31,    30,    22,    10,    25,    24,    28,    28,
      31,    15,    28,     7
=======
       0,    34,     0,     1,     3,     4,     5,     6,     8,    11,
      13,    14,    15,    19,    22,    25,    29,    31,     7,    25,
      25,    31,    31,     4,     4,     4,    31,    31,    31,     7,
      16,    18,    19,    20,    21,    31,    32,    32,     9,    12,
      25,    17,    31,    26,    31,    31,    31,    31,    31,    27,
      26,    26,    29,    30,    30,     4,    33,    31,    32,    24,
      10,    27,    26,    30,    30,    33,    17,    30,     7
>>>>>>> master
=======
       0,    35,     0,     1,     3,     4,     5,     6,     8,    11,
      13,    14,    15,    16,    20,    23,    26,    30,    32,     7,
      26,    26,    32,    32,     4,     4,     4,     4,    32,    32,
      32,     7,    17,    19,    20,    21,    22,    32,    33,    33,
       9,    12,    26,    18,    32,    27,    32,    32,    32,    32,
      32,    28,    27,    27,    30,    31,    31,     4,    34,    32,
      33,    25,    10,    28,    27,    31,    31,    34,    18,    31,
       7
>>>>>>> master
=======
       0,    35,     0,     1,     3,     4,     5,     6,     7,    10,
      12,    13,    14,    15,    19,    22,    25,    30,    32,    28,
      25,    25,    32,    32,     4,     4,     4,     4,    32,    32,
      32,    16,    18,    19,    20,    21,    32,    33,    33,     8,
      11,    25,    17,    32,    26,    32,    32,    32,    32,    32,
      27,    26,    26,    30,    31,    31,     4,    34,    32,    33,
      24,     9,    27,    26,    31,    31,    34,    17,    31
>>>>>>> master
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
       0,    26,    27,    27,    27,    27,    28,    28,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    30,    30,    31,    31,    32,    32,    32,    32
=======
       0,    28,    29,    29,    29,    29,    30,    30,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    32,    32,    33,    33,    34,    34,    34,
      34
>>>>>>> master
=======
       0,    29,    30,    30,    30,    30,    31,    31,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    33,    33,    34,    34,    35,    35,
      35,    35
>>>>>>> master
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     6,     4,     1,     0,     3,     3,     3,
<<<<<<< HEAD
       3,     3,     3,     2,     3,     2,     1,     4,     1,     1,
       3,     4,     1,     3,     1,     3,     0,     3,     9,     3
=======
       3,     3,     3,     2,     3,     2,     1,     1,     4,     1,
<<<<<<< HEAD
<<<<<<< HEAD
       4,     3,     4,     1,     3,     1,     3,     0,     3,     9,
       3
>>>>>>> master
=======
       4,     3,     2,     4,     1,     3,     1,     3,     0,     3,
       9,     3
>>>>>>> master
=======
       4,     3,     2,     4,     1,     3,     1,     3,     0,     2,
       8,     3
>>>>>>> master
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
  YYUSE (yytype);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
<<<<<<< HEAD
<<<<<<< HEAD
#line 40 "parser.y"
    { (yyval.a) = newflow('I', (yyvsp[-2].a), (yyvsp[0].a), NULL); }
#line 1276 "parser.tab.c"
    break;

  case 3:
#line 41 "parser.y"
    { (yyval.a) = newflow('I', (yyvsp[-4].a), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1282 "parser.tab.c"
    break;

  case 4:
#line 42 "parser.y"
    { (yyval.a) = newflow('W', (yyvsp[-2].a), (yyvsp[0].a), NULL); }
#line 1288 "parser.tab.c"
    break;

  case 6:
#line 46 "parser.y"
    { (yyval.a) = NULL; }
#line 1294 "parser.tab.c"
    break;

  case 7:
#line 47 "parser.y"
=======
#line 42 "parser.y"
=======
#line 41 "parser.y"
>>>>>>> master
    { (yyval.a) = newflow('I', (yyvsp[-2].a), (yyvsp[0].a), NULL); }
#line 1288 "parser.tab.c"
    break;

  case 3:
#line 42 "parser.y"
    { (yyval.a) = newflow('I', (yyvsp[-4].a), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1294 "parser.tab.c"
    break;

  case 4:
#line 43 "parser.y"
    { (yyval.a) = newflow('W', (yyvsp[-2].a), (yyvsp[0].a), NULL); }
#line 1300 "parser.tab.c"
    break;

  case 6:
#line 47 "parser.y"
    { (yyval.a) = NULL; }
#line 1306 "parser.tab.c"
    break;

  case 7:
<<<<<<< HEAD
#line 49 "parser.y"
>>>>>>> master
=======
#line 48 "parser.y"
>>>>>>> master
    { if ((yyvsp[0].a) == NULL)
	                (yyval.a) = (yyvsp[-2].a);
                      else
			(yyval.a) = newast('L', (yyvsp[-2].a), (yyvsp[0].a));
                    }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#line 1304 "parser.tab.c"
    break;

  case 8:
#line 54 "parser.y"
    { (yyval.a) = newcmp((yyvsp[-1].fn), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1310 "parser.tab.c"
    break;

  case 9:
#line 55 "parser.y"
    { (yyval.a) = newast('+', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1316 "parser.tab.c"
    break;

  case 10:
#line 56 "parser.y"
    { (yyval.a) = newast('-', (yyvsp[-2].a),(yyvsp[0].a));}
#line 1322 "parser.tab.c"
=======
#line 1316 "parser.tab.c"
>>>>>>> master
    break;

  case 11:
#line 57 "parser.y"
    { (yyval.a) = newast('*', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1328 "parser.tab.c"
    break;

  case 12:
#line 58 "parser.y"
    { (yyval.a) = newast('/', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1334 "parser.tab.c"
    break;

  case 13:
#line 59 "parser.y"
    { (yyval.a) = newast('|', (yyvsp[0].a), NULL); }
#line 1340 "parser.tab.c"
    break;

  case 14:
#line 60 "parser.y"
    { (yyval.a) = (yyvsp[-1].a); }
#line 1346 "parser.tab.c"
    break;

  case 15:
#line 61 "parser.y"
    { (yyval.a) = newast('M', (yyvsp[0].a), NULL); }
#line 1352 "parser.tab.c"
    break;

  case 16:
#line 62 "parser.y"
    { (yyval.a) = newnum((yyvsp[0].d)); }
#line 1358 "parser.tab.c"
    break;

  case 17:
#line 63 "parser.y"
    { (yyval.a) = newfunc((yyvsp[-3].fn), (yyvsp[-1].a)); }
#line 1364 "parser.tab.c"
    break;

  case 18:
#line 64 "parser.y"
    { (yyval.a) = newref((yyvsp[0].s)); }
#line 1370 "parser.tab.c"
    break;

  case 19:
#line 65 "parser.y"
    { (yyval.a) = newref((yyvsp[0].s)); }
#line 1376 "parser.tab.c"
    break;

  case 20:
#line 66 "parser.y"
    { (yyval.a) = newasgn((yyvsp[-2].s), (yyvsp[0].a)); }
#line 1382 "parser.tab.c"
    break;

  case 21:
#line 67 "parser.y"
    { (yyval.a) = newcall((yyvsp[-3].s), (yyvsp[-1].a)); }
#line 1388 "parser.tab.c"
    break;

  case 23:
#line 71 "parser.y"
    { (yyval.a) = newast('L', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1394 "parser.tab.c"
    break;

  case 24:
#line 73 "parser.y"
    { (yyval.sl) = newsymlist((yyvsp[0].s), NULL); }
#line 1400 "parser.tab.c"
    break;

  case 25:
#line 74 "parser.y"
    { (yyval.sl) = newsymlist((yyvsp[-2].s), (yyvsp[0].sl)); }
#line 1406 "parser.tab.c"
    break;

  case 27:
#line 78 "parser.y"
=======
#line 1317 "parser.tab.c"
=======
#line 1322 "parser.tab.c"
>>>>>>> master
    break;

  case 8:
#line 55 "parser.y"
    { (yyval.a) = newcmp((yyvsp[-1].fn), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1322 "parser.tab.c"
    break;

  case 9:
#line 56 "parser.y"
    { (yyval.a) = newast('+', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1328 "parser.tab.c"
    break;

  case 10:
#line 57 "parser.y"
    { (yyval.a) = newast('-', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1334 "parser.tab.c"
    break;

  case 11:
#line 58 "parser.y"
    { (yyval.a) = newast('*', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1340 "parser.tab.c"
    break;

  case 12:
#line 59 "parser.y"
    { (yyval.a) = newast('/', (yyvsp[-2].a),(yyvsp[0].a)); }
#line 1346 "parser.tab.c"
    break;

  case 13:
#line 60 "parser.y"
    { (yyval.a) = newast('|', (yyvsp[0].a), NULL); }
#line 1352 "parser.tab.c"
    break;

  case 14:
#line 61 "parser.y"
    { (yyval.a) = (yyvsp[-1].a); }
#line 1358 "parser.tab.c"
    break;

  case 15:
#line 62 "parser.y"
    { (yyval.a) = newast('M', (yyvsp[0].a), NULL); }
#line 1364 "parser.tab.c"
    break;

  case 16:
#line 63 "parser.y"
    { (yyval.a) = newnum((yyvsp[0].d)); }
#line 1370 "parser.tab.c"
    break;

  case 17:
#line 64 "parser.y"
    { (yyval.a) = newref((yyvsp[0].s)); }
#line 1376 "parser.tab.c"
    break;

  case 18:
#line 65 "parser.y"
    { (yyval.a) = newfunc((yyvsp[-3].fn), (yyvsp[-1].a)); }
#line 1382 "parser.tab.c"
    break;

  case 19:
#line 66 "parser.y"
    { (yyval.a) = newref((yyvsp[0].s)); }
#line 1388 "parser.tab.c"
    break;

  case 20:
#line 67 "parser.y"
    { (yyval.a) = newasgn((yyvsp[-2].s), (yyvsp[0].a)); }
#line 1394 "parser.tab.c"
    break;

  case 21:
#line 68 "parser.y"
    { (yyval.a) = newasgn((yyvsp[-1].s),(yyvsp[0].a)); }
#line 1400 "parser.tab.c"
    break;

  case 22:
#line 69 "parser.y"
    { ;}
#line 1406 "parser.tab.c"
    break;

  case 23:
#line 70 "parser.y"
    { (yyval.a) = newcall((yyvsp[-3].s), (yyvsp[-1].a)); }
#line 1412 "parser.tab.c"
    break;

  case 25:
#line 74 "parser.y"
    { (yyval.a) = newast('L', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 1418 "parser.tab.c"
    break;

  case 26:
#line 76 "parser.y"
    { (yyval.sl) = newsymlist((yyvsp[0].s), NULL); }
#line 1424 "parser.tab.c"
    break;

  case 27:
#line 77 "parser.y"
    { (yyval.sl) = newsymlist((yyvsp[-2].s), (yyvsp[0].sl)); }
#line 1430 "parser.tab.c"
    break;

<<<<<<< HEAD
  case 28:
#line 81 "parser.y"
>>>>>>> master
=======
  case 29:
<<<<<<< HEAD
#line 82 "parser.y"
>>>>>>> master
=======
#line 81 "parser.y"
>>>>>>> master
    {
    if(debug) dumpast((yyvsp[0].a), 0);
     printf("= %4.4g\n> ", eval((yyvsp[0].a)));
     treefree((yyvsp[0].a));
    }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#line 1416 "parser.tab.c"
    break;

  case 28:
#line 83 "parser.y"
    {
                       dodef((yyvsp[-6].s), (yyvsp[-4].sl), (yyvsp[-1].a));
                       printf("Defined %s\n> ", (yyvsp[-6].s)->name); }
#line 1424 "parser.tab.c"
    break;

  case 29:
#line 87 "parser.y"
    { yyerrok; printf("> "); }
#line 1430 "parser.tab.c"
    break;


#line 1434 "parser.tab.c"
=======
#line 1435 "parser.tab.c"
=======
#line 1446 "parser.tab.c"
>>>>>>> master
=======
#line 1440 "parser.tab.c"
>>>>>>> master
    break;

  case 30:
#line 86 "parser.y"
    {
                       dodef((yyvsp[-5].s), (yyvsp[-3].sl), (yyvsp[0].a));
                       printf("Defined %s\n> ", (yyvsp[-5].s)->name); }
#line 1448 "parser.tab.c"
    break;

  case 31:
#line 90 "parser.y"
    { yyerrok; printf("> "); }
#line 1454 "parser.tab.c"
    break;


<<<<<<< HEAD
<<<<<<< HEAD
#line 1453 "parser.tab.c"
>>>>>>> master
=======
#line 1464 "parser.tab.c"
>>>>>>> master
=======
#line 1458 "parser.tab.c"
>>>>>>> master

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
  return yyresult;
}
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#line 89 "parser.y"
=======
#line 92 "parser.y"
>>>>>>> master
=======
#line 93 "parser.y"
>>>>>>> master
=======
#line 92 "parser.y"
>>>>>>> master

