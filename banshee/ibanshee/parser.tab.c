/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 33 "parser.y" /* yacc.c:339  */

#include "nonspec.h"
#include "regions.h"
#include "hash.h"
#include "banshee_persist_kinds.h"
#include "banshee_region_persist_kinds.h"

static region ibanshee_region;
static hash_table constructor_env;
static hash_table named_env;
static hash_table var_env;
static int interactive = 1;
static sort_kind current_row_base_sort;

extern FILE *yyin;

void ibanshee_error_handler(gen_e e1, gen_e e2, banshee_error_kind bek) 
{
  fprintf(stderr,"Warning: ");
  switch(bek) {
  case bek_cons_mismatch:         // c(...) <= d(...)
    fprintf(stderr, "constructor mismatch (inconsistent constraint) ");
    break;
  case bek_occurs_check:	// occurs check failed (cyclic unification)
    fprintf(stderr, "occurs check failure ");
    break;
  default:
    fprintf(stderr, "unknown error ");
  }
  fprintf(stderr,"between expressions: ");
  expr_print(stderr,e1);
  fprintf(stderr," and ");
  expr_print(stderr,e2);
  fprintf(stderr,"\n");
}

static void save_cs(const char *filename)
{
  FILE *f;
  hash_table entry_points[3] = {constructor_env,named_env,var_env};
  
  f = fopen(filename, "wb");
  
  assert(f);

  serialize_cs(f, entry_points, 3);
}

static void rsave_cs(const char *filename)
{
  FILE *f;
  f = fopen(filename, "wb");
  assert(f);

  fwrite((void *)&constructor_env, sizeof(hash_table), 1, f);
  fwrite((void *)&named_env, sizeof(hash_table), 1, f);
  fwrite((void *)&var_env, sizeof(hash_table), 1, f);
  
  serialize(get_persistent_regions("extras"), "data", "offsets");
  write_module_nonspec(f);
}

extern region *get_persistent_regions(const char *filename);

static void rload_cs(const char *filename)
{
  FILE *f;
  translation t;
  region temp = newregion();
  f = fopen(filename, "rb");

  assert(f);

  t = deserialize("data","offsets", get_updater_functions("extras"), temp);

  fread((void *)&constructor_env, sizeof(hash_table), 1, f);
  fread((void *)&named_env, sizeof(hash_table), 1, f);
  fread((void *)&var_env, sizeof(hash_table), 1, f);

  update_pointer(t, (void **)&constructor_env);
  update_pointer(t, (void **)&named_env);
  update_pointer(t, (void **)&var_env);

  update_module_nonspec(t, f);
}


static void load_cs(const char *filename)
{
  FILE *f = fopen(filename, "rb");
  hash_table *entry_points = deserialize_cs(f);
  constructor_env = entry_points[0];
  named_env = entry_points[1];
  var_env = entry_points[2];
}

static void show_help()
{
  printf("--- iBanshee Quick Reference ---\n\
ident            : [A-Z a-z]([A-Z a-z 0-9 _])*\n\
integers (i)     : [0-9]+\n\
\n\
Variables (v)    : '{ident}\n\
Constructors (c) : {ident}\n\
Labels (l)       : {ident}\n\
Names (n)        : {ident}\n\
\n\
Expressions (e)  : v | c | n | c(e1,...,en) | e1 && e2 | e1 || e2\n\
                 | <l1=e1,...,ln=en [| e]> | 0:s | 1:s | _:s\n\
                 | pat(c,i,e) | proj(c,i,e) | ( e ) | c^-i(e)\n\
\n\
sorts            : basesort | row(basesort)\n\
\n\
basesort         : setIF | term\n\
\n\
Var decl         : v : sort\n\
Constructor decl : c(s1,...,sn) : basesort\n\
Name decl        : n = e \n\
Sig (s)          : + sort | - sort | = sort\n\
\n\
Constraints      : e1 <= e2 | e1 == e2\n\
\n\
Commands         : !help\n\
                   !tlb e\n\
                   !ecr e\n\
                   !undo [i]\n\
                   !trace [i]\n\
                   !quit\n\
                   !save \"filename\"\n\
                   !load \"filename\"\n\
                   !rsave\n\
                   !rload\n\
                   !exit\n");
}

static void print_tlb(gen_e e) 
{
  gen_e_list sol = setif_tlb(e);
	       
  if (gen_e_list_length(sol) == 0) {
    printf("{}\n");
  }
  else {
    gen_e next;
    gen_e_list_scanner scan;
    
    gen_e_list_scan(sol,&scan);
    
    gen_e_list_next(&scan,&next);
    printf("{");
    expr_print(stdout,next);
    
    while(gen_e_list_next(&scan,&next)) {
      printf(", ");
      expr_print(stdout,next);
    }
    printf("}\n");
  }
}

static void ibanshee_init(void) {
  region_init();
  nonspec_init();
  register_error_handler(ibanshee_error_handler);

  ibanshee_region = newregion();
  constructor_env = 
    make_persistent_string_hash_table(32,
				      BANSHEE_PERSIST_KIND_constructor);
  named_env = 
    make_persistent_string_hash_table(32,
				      BANSHEE_PERSIST_KIND_gen_e);
  var_env = 
    make_persistent_string_hash_table(32,
				      BANSHEE_PERSIST_KIND_gen_e);
}

void flush_lexer(void);


#line 247 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
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
    TOK_INTEGER = 258,
    TOK_IDENT = 259,
    TOK_VAR = 260,
    TOK_LPAREN = 261,
    TOK_RPAREN = 262,
    TOK_LANGLE = 263,
    TOK_RANGLE = 264,
    TOK_REST = 265,
    TOK_POS = 266,
    TOK_NEG = 267,
    TOK_EQ = 268,
    TOK_DECL = 269,
    TOK_COMMA = 270,
    TOK_WILD = 271,
    TOK_COLON = 272,
    TOK_CMD = 273,
    TOK_QUOTE = 274,
    TOK_INTER = 275,
    TOK_UNION = 277,
    TOK_LEQ = 279,
    TOK_DEQ = 280,
    TOK_CARET = 281,
    TOK_LINE = 282,
    TOK_ERROR = 283,
    TOK_EOF = 284,
    TOK_SETIF = 285,
    TOK_TERM = 286,
    TOK_FLOW = 287,
    TOK_ROW = 288,
    TOK_PROJ = 289,
    TOK_PAT = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 267 "parser.y" /* yacc.c:355  */

  int num;
  char *str;
  gen_e expr;
  gen_e_list exprs;
  e_sort esort;
  sort_kind sort;
  sig_elt* sig_elt_ptr;
  flowrow_map rowmap;
  sig_elt_list sig;
  pattern pat;

#line 334 "parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 349 "parser.tab.c" /* yacc.c:358  */

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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  36
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  49
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   284,   284,   286,   290,   292,   294,   298,   300,   302,
     306,   335,   348,   364,   382,   388,   395,   402,   409,   418,
     420,   424,   433,   444,   446,   450,   452,   456,   468,   483,
     498,   505,   512,   516,   544,   553,   557,   562,   573,   577,
     583,   590,   595,   601,   611,   621,   634,   666,   677,   686
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_INTEGER", "TOK_IDENT", "TOK_VAR",
  "\"(\"", "\")\"", "\"<\"", "\">\"", "\"|\"", "\"+\"", "\"-\"", "\"=\"",
  "\"#\"", "\",\"", "\"_\"", "\":\"", "\"!\"", "\"\\\"\"", "TOK_INTER",
  "\"&&\"", "TOK_UNION", "\"||\"", "\"<=\"", "\"==\"", "\"^\"", "TOK_LINE",
  "TOK_ERROR", "TOK_EOF", "\"setIF\"", "\"term\"", "\"flow\"", "\"row\"",
  "\"proj\"", "\"pat\"", "$accept", "program", "line", "toplev", "decl",
  "signature", "sig_elt", "sort", "esort", "basesort", "constraint",
  "expr", "expr_list", "row", "rowmap", "pattern", "cmd", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

#define YYPACT_NINF -20

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-20)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      77,   -15,     1,    -2,    62,    25,    27,    48,   -20,   -20,
      57,    57,    42,   -20,    45,   -20,   -20,    29,   -20,   -11,
     110,    62,    72,    75,   -11,    -3,   -20,    68,    71,    80,
      -9,   -11,     5,    94,   -20,   -20,   -20,   -20,   -20,    62,
      62,    62,    62,   -20,   -20,    99,   -20,   -20,    31,    31,
      31,    18,   -20,    21,    19,    21,   -20,   105,   -20,    62,
     -20,    62,   -20,    62,   106,   -20,   -15,   113,    21,   109,
     103,   -20,    21,    21,    72,   124,   -20,   -20,   -20,   -20,
     114,   116,   -20,    62,   126,    21,    21,   120,   115,   132,
     129,    72,    72,   -20,    21,    62,    62,   -20,   122,   -20,
     131,   -20,    79,    21,    62,   -20,   -20,    87,   -20
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    28,    27,     0,     0,     0,     0,     4,     6,
       0,     0,     0,     2,     0,     7,     8,     0,     9,     0,
       0,     0,     0,     0,     0,    28,    27,     0,     0,     0,
      41,     0,    46,     0,    36,    35,     1,     3,     5,     0,
       0,     0,     0,    23,    24,     0,    33,    21,     0,     0,
       0,     0,    14,    39,     0,    11,    12,     0,    10,     0,
      38,     0,    32,     0,     0,    34,    47,     0,    49,     0,
      31,    30,    25,    26,     0,     0,    16,    19,    17,    18,
       0,     0,    29,     0,     0,    43,    42,     0,     0,     0,
       0,     0,     0,    15,    40,     0,     0,    48,     0,    22,
       0,    13,     0,    44,     0,    20,    37,     0,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -20,   -20,   127,   -20,   -20,   -20,    59,    70,   -19,   -18,
     -20,    -4,   -20,   -20,   -20,   130,   -20
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    51,    52,    76,    46,    47,
      16,    17,    54,    29,    30,    34,    18
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      27,    63,    19,    59,    56,    58,    64,    20,    66,    25,
      26,     4,    65,     5,    21,    24,    53,    55,    22,    43,
      44,     6,    45,    23,    67,    80,    82,    23,    68,    28,
      77,    77,    77,    81,    83,    70,    71,    72,    73,    10,
      11,    39,    36,    40,    31,     1,     2,     3,     4,    39,
       5,    40,    32,    41,    42,    53,    90,    85,     6,    86,
       7,    43,    44,    33,    75,     1,    25,    26,     4,     8,
       5,     9,    38,   100,   101,    60,    10,    11,     6,    94,
       1,     2,     3,     4,    61,     5,   106,    57,    39,    62,
      40,   102,   103,     6,   108,     7,    10,    11,    69,    39,
     107,    40,    43,    44,     8,    74,     9,    39,    84,    40,
      87,    10,    11,     1,    25,    26,     4,    88,     5,    78,
      79,    48,    49,    50,    89,    40,     6,    48,    49,    50,
      91,    92,    95,    96,    97,    98,    99,   104,   105,    37,
      93,    35,     0,     0,    10,    11
};

static const yytype_int8 yycheck[] =
{
       4,    10,    17,     6,    22,    24,    15,     6,     3,     4,
       5,     6,    31,     8,    13,    17,    20,    21,    17,    30,
      31,    16,    33,    26,    19,     7,     7,    26,    32,     4,
      48,    49,    50,    15,    15,    39,    40,    41,    42,    34,
      35,    20,     0,    22,    17,     3,     4,     5,     6,    20,
       8,    22,     4,    24,    25,    59,    74,    61,    16,    63,
      18,    30,    31,     6,    33,     3,     4,     5,     6,    27,
       8,    29,    27,    91,    92,     7,    34,    35,    16,    83,
       3,     4,     5,     6,    13,     8,     7,    12,    20,     9,
      22,    95,    96,    16,     7,    18,    34,    35,     4,    20,
     104,    22,    30,    31,    27,     6,    29,    20,     3,    22,
       4,    34,    35,     3,     4,     5,     6,     4,     8,    49,
      50,    11,    12,    13,    15,    22,    16,    11,    12,    13,
       6,    17,     6,    13,    19,     3,     7,    15,     7,    12,
      81,    11,    -1,    -1,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     8,    16,    18,    27,    29,
      34,    35,    37,    38,    39,    40,    46,    47,    52,    17,
       6,    13,    17,    26,    17,     4,     5,    47,     4,    49,
      50,    17,     4,     6,    51,    51,     0,    38,    27,    20,
      22,    24,    25,    30,    31,    33,    44,    45,    11,    12,
      13,    41,    42,    47,    48,    47,    45,    12,    44,     6,
       7,    13,     9,    10,    15,    44,     3,    19,    47,     4,
      47,    47,    47,    47,     6,    33,    43,    45,    43,    43,
       7,    15,     7,    15,     3,    47,    47,     4,     4,    15,
      45,     6,    17,    42,    47,     6,    13,    19,     3,     7,
      45,    45,    47,    47,    15,     7,     7,    47,     7
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    38,    38,    38,    39,    39,    39,
      40,    40,    40,    40,    41,    41,    42,    42,    42,    43,
      43,    44,    44,    45,    45,    46,    46,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    48,
      48,    49,    49,    50,    50,    51,    52,    52,    52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     1,     1,     1,
       3,     3,     3,     6,     1,     3,     2,     2,     2,     1,
       4,     1,     4,     1,     1,     3,     3,     1,     1,     4,
       3,     3,     3,     3,     3,     2,     2,     7,     3,     1,
       3,     1,     3,     3,     5,     7,     2,     3,     5,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
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
  unsigned long int yylno = yyrline[yyrule];
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
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
| yyreduce -- Do a reduction.  |
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
#line 285 "parser.y" /* yacc.c:1646  */
    { }
#line 1499 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 287 "parser.y" /* yacc.c:1646  */
    { }
#line 1505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 291 "parser.y" /* yacc.c:1646  */
    { if (interactive) YYACCEPT; }
#line 1511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 293 "parser.y" /* yacc.c:1646  */
    { if (interactive) YYACCEPT; }
#line 1517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 295 "parser.y" /* yacc.c:1646  */
    {exit(0);}
#line 1523 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 299 "parser.y" /* yacc.c:1646  */
    { }
#line 1529 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 301 "parser.y" /* yacc.c:1646  */
    {  }
#line 1535 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 303 "parser.y" /* yacc.c:1646  */
    { }
#line 1541 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 307 "parser.y" /* yacc.c:1646  */
    { 
	     gen_e fresh_var;

	     if (hash_table_lookup(var_env,(yyvsp[-2].str),NULL)) {
	      fprintf(stderr,"Attempted to redefine existing variable: %s",(yyvsp[-2].str));
	       YYABORT;
	     }
	     else {
	       switch((yyvsp[0].esort)) {
	       case e_setif_sort:
		 fresh_var = setif_fresh((yyvsp[-2].str));
		 break;
	       case e_term_sort:
		 fresh_var = term_fresh((yyvsp[-2].str));
		 break;
	       case e_flowrow_setif_sort:
		 fresh_var = flowrow_fresh((yyvsp[-2].str),setif_sort);
		 break;
	       case e_flowrow_term_sort:
                 fresh_var = flowrow_fresh((yyvsp[-2].str),term_sort); 
		 break;
	       }	     
	       hash_table_insert(var_env,rstrdup(banshee_nonptr_region,(yyvsp[-2].str)),fresh_var);
	       printf("var: ");
	       expr_print(stdout, fresh_var);
	       printf("\n");
	     }
	   }
#line 1574 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 336 "parser.y" /* yacc.c:1646  */
    {
	     if (hash_table_lookup(constructor_env,(yyvsp[-2].str),NULL)) {
	       fprintf(stderr,"Attempted to redefine existing constructor: %s",(yyvsp[-2].str));
	       YYABORT;
	     }
	     else {
	       hash_table_insert(named_env,rstrdup(banshee_nonptr_region, (yyvsp[-2].str)),(hash_data)(yyvsp[0].expr));
	       printf("%s: ",(yyvsp[-2].str));
	       expr_print(stdout,(yyvsp[0].expr));
	       printf("\n");
	     }
           }
#line 1591 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 349 "parser.y" /* yacc.c:1646  */
    {
	     if (hash_table_lookup(constructor_env,(yyvsp[-2].str),NULL)) {
               fprintf(stderr,"Attempted to redefine existing constructor: %s\n",(yyvsp[-2].str));
	       YYABORT;
	     }
             else if (hash_table_lookup(named_env,(yyvsp[-2].str),NULL)) {
	       fprintf(stderr,"Attempted to redefine existing expression: %s\n",(yyvsp[-2].str));
	       YYABORT;
 	     }
	     else {
               constructor c = make_constructor((yyvsp[-2].str),(yyvsp[0].sort),NULL,0);
	       hash_table_insert(constructor_env,rstrdup(banshee_nonptr_region, (yyvsp[-2].str)),(hash_data)c);
	       printf("constructor: %s\n", (yyvsp[-2].str));
	     }
           }
#line 1611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 365 "parser.y" /* yacc.c:1646  */
    { 
	     if (hash_table_lookup(constructor_env,(yyvsp[-5].str),NULL)) {
               fprintf(stderr,"Attempted to redefine existing constructor: %s\n",(yyvsp[-5].str));
	       YYABORT;
	     }
             else if (hash_table_lookup(named_env,(yyvsp[-5].str),NULL)) {
	       fprintf(stderr,"Attempted to redefine existing expression: %s\n",(yyvsp[-5].str));
	       YYABORT;
 	     }
	     else {
               constructor c = make_constructor_from_list((yyvsp[-5].str),(yyvsp[0].sort),sig_elt_list_reverse((yyvsp[-3].sig)));
	       hash_table_insert(constructor_env,rstrdup(banshee_nonptr_region, (yyvsp[-5].str)),c);
	       printf("constructor: %s\n", (yyvsp[-5].str));
	     }
           }
#line 1631 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 383 "parser.y" /* yacc.c:1646  */
    { 
             sig_elt_list sig = new_sig_elt_list(ibanshee_region);
             sig_elt_list_cons((yyvsp[0].sig_elt_ptr),sig);
             (yyval.sig) = sig;
           }
#line 1641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 389 "parser.y" /* yacc.c:1646  */
    {
             sig_elt_list_cons((yyvsp[0].sig_elt_ptr),(yyvsp[-2].sig));
             (yyval.sig) = (yyvsp[-2].sig); 
           }
#line 1650 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 396 "parser.y" /* yacc.c:1646  */
    {
	     sig_elt *eltptr = ralloc(banshee_nonptr_region,sig_elt);
	     eltptr->variance = vnc_pos;
	     eltptr->sort = (yyvsp[0].sort);
	     (yyval.sig_elt_ptr) = eltptr;
           }
#line 1661 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 403 "parser.y" /* yacc.c:1646  */
    {
	     sig_elt *eltptr = ralloc(banshee_nonptr_region,sig_elt);
	     eltptr->variance = vnc_neg;
	     eltptr->sort = (yyvsp[0].sort);
	     (yyval.sig_elt_ptr) = eltptr;
           }
#line 1672 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 410 "parser.y" /* yacc.c:1646  */
    {
	     sig_elt *eltptr = ralloc(banshee_nonptr_region,sig_elt);
	     eltptr->variance = vnc_non;
	     eltptr->sort = (yyvsp[0].sort);
	     (yyval.sig_elt_ptr) = eltptr;
           }
#line 1683 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 419 "parser.y" /* yacc.c:1646  */
    { (yyval.sort) = (yyvsp[0].sort);}
#line 1689 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 421 "parser.y" /* yacc.c:1646  */
    { (yyval.sort) = flowrow_sort; }
#line 1695 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 425 "parser.y" /* yacc.c:1646  */
    {
             switch((yyvsp[0].sort)) {
 	       case setif_sort: (yyval.esort) = e_setif_sort; break;
               case term_sort: (yyval.esort) = e_term_sort; break;
	     default: fprintf(stderr,"Bad base sort\n");
	       YYABORT;
	     } 
           }
#line 1708 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 434 "parser.y" /* yacc.c:1646  */
    { 
             switch((yyvsp[-1].sort)) {
	       case setif_sort: (yyval.esort) = e_flowrow_setif_sort; break;
               case term_sort: (yyval.esort) = e_flowrow_term_sort; break;
	     default: fprintf(stderr,"Bad base sort\n");
	       YYABORT;
	     }
           }
#line 1721 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 445 "parser.y" /* yacc.c:1646  */
    { (yyval.sort) = setif_sort; }
#line 1727 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 447 "parser.y" /* yacc.c:1646  */
    { (yyval.sort) = term_sort; }
#line 1733 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 451 "parser.y" /* yacc.c:1646  */
    { call_sort_inclusion((yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 1739 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 453 "parser.y" /* yacc.c:1646  */
    { call_sort_unify((yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 1745 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 457 "parser.y" /* yacc.c:1646  */
    { 
	     gen_e v = NULL;
	     
	     if (hash_table_lookup(var_env,(yyvsp[0].str),(hash_data*)&v)) {
	       (yyval.expr) = v;
	     }
	     else {
	       fprintf(stderr,"Could not find variable: %s\n",(yyvsp[0].str));
	       YYABORT;
	     }
           }
#line 1761 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 469 "parser.y" /* yacc.c:1646  */
    {
	     constructor c = NULL;
	     gen_e n = NULL;
             if (hash_table_lookup(constructor_env,(yyvsp[0].str),(hash_data *)&c)) {
	       (yyval.expr) = constructor_expr(c,NULL,0);
	     }
	     else if (hash_table_lookup(named_env,(yyvsp[0].str),(hash_data*)&n)) {
	       (yyval.expr) = n;
	     }
	     else {
	       fprintf(stderr,"Could not find constant or named expression: %s\n",(yyvsp[0].str));
	       YYABORT;
	     }
           }
#line 1780 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 484 "parser.y" /* yacc.c:1646  */
    {
	     constructor c = NULL;

	     if (hash_table_lookup(constructor_env,(yyvsp[-3].str),(hash_data *)&c)) {
	       (yyval.expr) = 
		 constructor_expr(c,
				  gen_e_list_array_from_list(ibanshee_region,gen_e_list_reverse((yyvsp[-1].exprs))),
				  gen_e_list_length((yyvsp[-1].exprs)));
	     }
	     else {
	       fprintf(stderr,"Could not find constructor: %s\n",(yyvsp[-3].str));
	       YYABORT;
	     }
           }
#line 1799 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 499 "parser.y" /* yacc.c:1646  */
    {
             gen_e_list exprs = new_gen_e_list(ibanshee_region); 
             gen_e_list_cons((yyvsp[-2].expr), exprs);
             gen_e_list_cons((yyvsp[0].expr), exprs); 
             (yyval.expr) = setif_union(exprs);
           }
#line 1810 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 506 "parser.y" /* yacc.c:1646  */
    { 
             gen_e_list exprs = new_gen_e_list(ibanshee_region); 
             gen_e_list_cons((yyvsp[-2].expr), exprs);
             gen_e_list_cons((yyvsp[0].expr), exprs); 
             (yyval.expr) = setif_inter(exprs);
           }
#line 1821 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 513 "parser.y" /* yacc.c:1646  */
    {
             (yyval.expr) = (yyvsp[-1].expr);
           }
#line 1829 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 517 "parser.y" /* yacc.c:1646  */
    { 
             if ((yyvsp[-2].num) == 1) {
              switch((yyvsp[0].esort)) {
	       case e_setif_sort: (yyval.expr) = setif_one(); break;
	       case e_term_sort: (yyval.expr) = term_one(); break;
	       case e_flowrow_setif_sort: (yyval.expr) = flowrow_one(setif_sort); break;
	       case e_flowrow_term_sort: (yyval.expr) = flowrow_one(term_sort); break;
	       default: fprintf(stderr,"Invalid sort for zero expression\n");
		 YYABORT;
              } 

             }
             else if ((yyvsp[-2].num) == 0) {
              switch((yyvsp[0].esort)) {
	       case e_setif_sort: (yyval.expr) = setif_zero(); break;
	       case e_term_sort: (yyval.expr) = term_zero(); break;
	       case e_flowrow_setif_sort: (yyval.expr) = flowrow_zero(setif_sort); break;
	       case e_flowrow_term_sort: (yyval.expr) = flowrow_zero(term_sort); break;
	       default: fprintf(stderr,"Invalid sort for one expression\n");
		 YYABORT;
	      } 
	     }
             else {
               fprintf(stderr,"Invalid expression\n");
	       YYABORT;
	     }
           }
#line 1861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 545 "parser.y" /* yacc.c:1646  */
    { 
             switch((yyvsp[0].esort)) {
	     case e_flowrow_setif_sort: (yyval.expr) = flowrow_wild(setif_sort); break;
	     case e_flowrow_term_sort: (yyval.expr) = flowrow_wild(term_sort); break;
	     default: fprintf(stderr,"Invalid sort for wildcard expression\n");
	       YYABORT;
             }  
           }
#line 1874 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 554 "parser.y" /* yacc.c:1646  */
    { 
             (yyval.expr) = setif_proj_pat((yyvsp[0].pat).c,(yyvsp[0].pat).i,(yyvsp[0].pat).e); 
           }
#line 1882 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 558 "parser.y" /* yacc.c:1646  */
    { 
             (yyval.expr) = setif_proj((yyvsp[0].pat).c,(yyvsp[0].pat).i,(yyvsp[0].pat).e); 
           }
#line 1890 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 563 "parser.y" /* yacc.c:1646  */
    {
	     constructor c = NULL;

	     if (!hash_table_lookup(constructor_env,(yyvsp[-6].str),(hash_data *)&c)) {
	       fprintf(stderr,"Could not find constructor: %s\n",(yyvsp[-6].str));
	       YYABORT;
	     }
             assert(c);
             (yyval.expr) = setif_proj(c,(yyvsp[-3].num),(yyvsp[-1].expr));
           }
#line 1905 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 574 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1911 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 578 "parser.y" /* yacc.c:1646  */
    {
             gen_e_list exprs = new_gen_e_list(ibanshee_region);
             gen_e_list_cons((yyvsp[0].expr),exprs);
             (yyval.exprs) = exprs; 
           }
#line 1921 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 584 "parser.y" /* yacc.c:1646  */
    {
             gen_e_list_cons((yyvsp[0].expr),(yyvsp[-2].exprs));
             (yyval.exprs) = (yyvsp[-2].exprs);
           }
#line 1930 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 591 "parser.y" /* yacc.c:1646  */
    { 
             (yyval.expr) = flowrow_make_row((yyvsp[0].rowmap), flowrow_fresh("'rest", 
						     current_row_base_sort ));
           }
#line 1939 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 596 "parser.y" /* yacc.c:1646  */
    { 
             (yyval.expr) = flowrow_make_row((yyvsp[-2].rowmap), (yyvsp[0].expr));
           }
#line 1947 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 602 "parser.y" /* yacc.c:1646  */
    {
	     flowrow_field field;
	     flowrow_map map;
	     map = new_flowrow_map(ibanshee_region);
	     current_row_base_sort = expr_sort((yyvsp[0].expr));
	     field = flowrow_make_field((yyvsp[-2].str),(yyvsp[0].expr));
	     flowrow_map_cons(field,map);
	     (yyval.rowmap) = map;
           }
#line 1961 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 612 "parser.y" /* yacc.c:1646  */
    {
	     flowrow_field field;
	     current_row_base_sort = expr_sort((yyvsp[0].expr));
             field = flowrow_make_field((yyvsp[-2].str),(yyvsp[0].expr));
             flowrow_map_cons(field,(yyvsp[-4].rowmap));
             (yyval.rowmap) = (yyvsp[-4].rowmap);
           }
#line 1973 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 622 "parser.y" /* yacc.c:1646  */
    { 
	     constructor c = NULL;
	     if (hash_table_lookup(constructor_env,(yyvsp[-5].str),(hash_data *)&c)) {
	       (yyval.pat) = (pattern){c,(yyvsp[-3].num),(yyvsp[-1].expr)}; 
	     }
	     else {
	       fprintf(stderr,"Could not find constructor: %s\n",(yyvsp[-5].str));
	       YYABORT;
	     }
	   }
#line 1988 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 635 "parser.y" /* yacc.c:1646  */
    {
	     if (!strcmp((yyvsp[0].str),"quit")) {
	       exit(0);
	     }
	     else if (!strcmp((yyvsp[0].str),"exit")) {
               exit(0);
	     }
	     else if (!strcmp((yyvsp[0].str),"undo")) {
	       banshee_rollback();
	     }
	     else if (!strcmp((yyvsp[0].str),"help")) {
	       show_help();
	     }
	     else if (!strcmp((yyvsp[0].str),"rsave")) {
	       rsave_cs("statics");
	     }
	     else if (!strcmp((yyvsp[0].str),"rload")) {
	       rload_cs("statics");
	     }
             else if (!strcmp((yyvsp[0].str),"save") || !strcmp((yyvsp[0].str),"load")) {
	       fprintf(stderr,"Missing filename\n");
	     }
	     /* TODO */
	     else if (!strcmp((yyvsp[0].str),"trace")) {
	       fprintf(stderr,"Trace not yet implemented\n");
	     }
	     else {
	       fprintf(stderr,"Unrecognized command: %s\n",(yyvsp[0].str));
	       YYABORT;
	     }
	   }
#line 2024 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 667 "parser.y" /* yacc.c:1646  */
    {
	     if (!strcmp((yyvsp[-1].str),"undo")) {
	       banshee_backtrack((yyvsp[0].num));
	     }
	     /* TODO */
	     else if (!strcmp((yyvsp[-1].str),"trace")) {
	       fprintf(stderr,"Trace not yet implemented\n");
	     }
	   }
#line 2038 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 678 "parser.y" /* yacc.c:1646  */
    {
             if (!strcmp((yyvsp[-3].str),"save")) {
	       save_cs((yyvsp[-1].str));
	     }
	     else if (!strcmp((yyvsp[-3].str),"load")) {
	       load_cs((yyvsp[-1].str));
	     }
           }
#line 2051 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 687 "parser.y" /* yacc.c:1646  */
    { 
	     if (!strcmp((yyvsp[-1].str),"tlb")) {
	       print_tlb((yyvsp[0].expr));
	     }
	     else if (!strcmp((yyvsp[-1].str),"ecr")) {
	       expr_print(stdout,term_get_ecr((yyvsp[0].expr)));
	       printf("\n");
	     }
	   }
#line 2065 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2069 "parser.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
#line 698 "parser.y" /* yacc.c:1906  */

int main(int argc, char **argv) {
  ibanshee_init();
  
  if (argc > 1) {
    if (!strcmp(argv[1],"-f")) {
      yyin = fopen(argv[2],"r");
      interactive = 0;
      
      if (yyin == NULL) {
	fprintf(stderr,"Failed to open file: %s\n",argv[2]);
      }
      else {
	if (yyparse()) {
	  fprintf(stderr,"Warning: some errors occurred\n");
	  exit(1);
	}
	else {
	  exit(0);
	}
      }
    }
  }


  if (interactive) {
    printf("iBanshee version 0.1\n");
    do {
      int time = banshee_get_time();
      printf("[%d] > ",time);
      fflush(stdout);
      
      if (yyparse()) { /* error parsing the line, ignore the remaining input */
	flush_lexer();
      }
    }
    while (1);
  }
}

