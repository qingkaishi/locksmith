/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
#line 267 "parser.y" /* yacc.c:1909  */

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

#line 101 "parser.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
