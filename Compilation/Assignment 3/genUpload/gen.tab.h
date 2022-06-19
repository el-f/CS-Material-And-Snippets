/* A Bison parser, made by GNU Bison 3.5.0.  */

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

#ifndef YY_YY_GEN_TAB_H_INCLUDED
# define YY_YY_GEN_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 48 ".\\gen.y"

    void errorMsg (const char *format, ...);
    enum {NSIZE = 100}; // max size of variable names
    enum type {_INT, _DOUBLE };
	enum op { PLUS, MINUS, MUL, DIV, PLUS_PLUS, MINUS_MINUS };
	
	typedef int LABEL;  /* symbolic label. Symbolic labels are named
                       label1, label2, ... in the generated code 
					   but inside the compiler they may be represented as
					   integers. For example,  symbolic label 'label3' 
					   is represented as 3.
					 */
    struct exp { /* semantic value for expression */
	    char result[NSIZE]; /* result of expression is stored 
   		   in this variable. If result is a constant number
		   then the number is stored here (as a string) */
	    enum type type;     // type of expression
	};
	
	struct caselist { /* semantic value for 'caselist' */
	    char switch_result[NSIZE]; /* result variable of the switch expression */
                   /* you will probably need to add another member
                         to this structure */				   
    };			   
	

#line 75 "gen.tab.h"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_NUM = 258,
    DOUBLE_NUM = 259,
    RELOP = 260,
    ID = 261,
    ADDOP = 262,
    MULOP = 263,
    INC = 264,
    WHILE = 265,
    IF = 266,
    ELSE = 267,
    FOR = 268,
    SWITCH = 269,
    CASE = 270,
    DEFAULT = 271,
    BREAK = 272,
    INT = 273,
    DOUBLE = 274,
    INPUT = 275,
    OUTPUT = 276
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 78 ".\\gen.y"

   char name[NSIZE];
   int ival;
   double dval;
   enum op op;
   struct exp e;
   LABEL label;
   const char *relop;
   enum type type;
   struct caselist cl;

#line 120 "gen.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GEN_TAB_H_INCLUDED  */
