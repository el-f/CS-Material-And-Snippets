%{
#include <string.h>
#include <stdio.h>
#include "tennis.h"

extern int atoi (const char *);
extern void exit(int);

union _lval lex_val; // current token value

%}

%option noyywrap
%option yylineno

%x P_NAME

/* valid year format: any year from the year 1900 */
year_format (19[0-9]{2})|([2-9][0-9]{3,})

%%
\*\*.*\*\*              { return TITLE; }
"<name>"                { return NAME; }
"<Wimbledon>"           { return WIMBLEDON; }
"<Australian Open>"	    { return AUSTRALIAN_OPEN; }
"<French Open>"	        { return FRENCH_OPEN; }

{year_format}           { lex_val.year = atoi(yytext); return YEAR; }

\-                      { return '-'; }

\<Woman\>|\<Man\>       { strcpy(lex_val.gender,yytext); return GENDER; }

\," "                   { return ','; }

\"|\'                   { BEGIN (P_NAME); }

<P_NAME>[a-zA-Z]+|[a-zA-Z]+" "[a-zA-Z]+ { strcpy(lex_val.player_name, yytext); return PLAYER_NAME; }
<P_NAME>\"|\'           { BEGIN (0); }

[\t\r\n ]+              /* skip white spaces */

.                       { fprintf (stderr, "unrecognized token %c\n", yytext[0]);    exit(1);}

%%

/* useful for error messages */
char *token_name(enum token token) {
    static char *names[] = {
         "EOF", "TITLE", "NAME", "PLAYER_NAME", "GENDER",
         "WIMBLEDON", "FRENCH_OPEN", "AUSTRALIAN_OPEN", "YEAR"
    };
    return token <= YEAR ? names[token] : "unknown token";
}
