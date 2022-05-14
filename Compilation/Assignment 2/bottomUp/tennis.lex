%{
#include "tennis.tab.h" // bison
extern int atoi (const char *);
extern void exit(int);

int linenum = 1;

%}
%option noyywrap

%x P_NAME

/* valid year format: any year from the year 1900 */
year_format (19[0-9]{2})|([2-9][0-9]{3,})

%%
\*\*.*\*\*              { return TITLE; }
"<name>"                { return NAME; }
"<Wimbledon>"           { return WIMBLEDON; }
"<Australian Open>"	    { return AUSTRALIAN_OPEN; }
"<French Open>"	        { return FRENCH_OPEN; }

{year_format}           { yylval.year = atoi(yytext); return YEAR; }

\-                      { return '-'; }

\<Woman\>|\<Man\>       { strcpy(yylval.gender,yytext); return GENDER; }

\," "                   { return ','; }

\"|\'                   { BEGIN (P_NAME); }

<P_NAME>[a-zA-Z]+|[a-zA-Z]+" "[a-zA-Z]+ { strcpy(yylval.player_name, yytext); return PLAYER_NAME; }
<P_NAME>\"|\'           { BEGIN (0); }

[\t\r ]+              	/* skip white spaces */
\n						{ linenum++; }

.                       { fprintf (stderr, "unrecognized token %c\n", yytext[0]);    exit(1);}

%%