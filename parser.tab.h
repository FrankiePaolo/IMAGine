/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 81 "parser.tab.h"
=======
#line 84 "parser.tab.h"
>>>>>>> master
=======
#line 85 "parser.tab.h"
>>>>>>> master
=======
#line 84 "parser.tab.h"
>>>>>>> master

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
