%{
/*
 *  Authors: Elazar Fine, Maor Ofek
 */
#include <string.h>

// ordered by expected appearance in file
#define NAME 301
#define GENDER 302
#define TOURNEY 303
#define YEAR 304
#define YEAR_RANGE 305

union {
    char name[50];
    char gender[9];
    char tourney[20];
    int  year;
    char year_range[10];
} yylval;

unsigned int line_num = 1;

extern int atoi (const char *);

%}

%option noyywrap

/* exclusive start condition -- deals with C++ style comments */ 
%x PLAYERNAME
%x TOURNAMENT

/* valid name format: either 'first last' or 'single' */
name_format [a-zA-Z]+|[a-zA-Z]+" "[a-zA-Z]+
/* valid year format: any year from the year 1900 */
year_format (19[0-9]{2})|([2-9][0-9]{3,})
%%

\*\*" "[a-zA-Z]*" "\*\*         // possible title of file (`** Winners **`) - just ignore if appears

\<name\>" "*[\"\']?             { BEGIN (PLAYERNAME); }
<PLAYERNAME>{name_format}       { strcpy(yylval.name, yytext);          return NAME; }
<PLAYERNAME>[\"\'\t]?" "*       { BEGIN (0); }

\<Woman\>|\<Man\>               { strcpy (yylval.gender, yytext);       return GENDER; }

\<                              { BEGIN (TOURNAMENT); }
<TOURNAMENT>{name_format}       { strcpy(yylval.tourney, yytext);       return TOURNEY; }
<TOURNAMENT>\>                  { BEGIN (0); }

{year_format}                   { yylval.year = atoi (yytext);          return YEAR; }

{year_format}\-{year_format}    { strcpy (yylval.year_range, yytext);   return YEAR_RANGE; }

\n|\r\n                         { line_num++; } // count lines
[\t\, ]+                        /* skip white space and commas */

.                               { fprintf (stderr, "unrecognized token [ %c ] at line [ %d ]\n", yytext[0], line_num); }

%%

int main (int argc, char **argv) {
	int token;

	if (argc != 2) {
		fprintf(stderr, "Usage: mylex <input file name>\n");
		exit(1);
	}

	yyin = fopen (argv[1], "r");
    printf("%-10s | %-20s | %-25s\n", "TOKEN", "LEXEME", "SEMANTIC VALUE");
	printf("___________________________________________________________\n\n");
    int first = 1;
    while ((token = yylex()) != 0) {
        switch (token) {

            case NAME:
                if (first) first = 0;
                else printf("\n-----------------------------------------------------------\n\n");
                printf("%-10s | %-20s | %-25s\n", "NAME", yylval.name, yylval.name);
                break;

            case GENDER:
                printf("%-10s | %-20s | %-25s\n", "GENDER", yylval.gender, strcmp(yylval.gender, "<Man>") ? "WOMAN": "MAN");
                break;

            case TOURNEY:
                printf("\n%-10s | %-20s | %-25s\n", "TOURNEY", yylval.tourney, yylval.tourney);
                break;

            case YEAR:
                printf("%-10s | %-20d | %-25d\n", "YEAR", yylval.year, yylval.year);
                break;

            case YEAR_RANGE:
                printf("%-10s | %-20s | %-25s\n", "YEAR_RANGE", yylval.year_range, yylval.year_range);
                break;

            default:
                fprintf(stderr, "Error! invalid token identifier: [ %d ]\n", token);
                exit(1);
        }
    }
	fclose(yyin);
	exit(0);
}
