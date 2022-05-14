%code {

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern 	int yylex(void);
void 	yyerror(const char *s);
int 	years_in_range(int range_start, int range_end);

}

%code requires {
    typedef struct {
		char   name[80];
		char   gender[10];
		int    wins;
    } Player;
}

%union {
	int year;
	char player_name[80];
	char gender[10];
	int wins;
	int list_of_years;
	Player player;
	int optional_french_open;
	int optional_australian_open;
	int optional_wimbledon;
}

%token <player> NAME PLAYER_NAME GENDER
%token YEAR
%token WIMBLEDON FRENCH_OPEN AUSTRALIAN_OPEN
%token TITLE

%nterm <wins> year_spec
%nterm <player> list_of_players player
%nterm <list_of_years> list_of_years
%nterm <optional_australian_open> optional_australian_open
%nterm <optional_french_open> optional_french_open
%nterm <optional_wimbledon> optional_wimbledon


%define parse.error verbose /*%error-verbose*/

%%

input: TITLE list_of_players
	{ 
		if (strcmp($2.gender, "<Woman>") == 0) {
			printf("Woman with greatest number of wins at Wimbledon: %s (%d wins)\n",
			        $2.name,
			        $2.wins);
		} else {
		    puts("Did not find a woman player!");
		}

	};


list_of_players: list_of_players player
	{
		if (strcmp($2.gender, "<Woman>") == 0) {
			$$ = $1.wins >= $2.wins ? $1 : $2; // get max
		} // else $$ = $1 (by default)
	};

list_of_players: player;


player: NAME PLAYER_NAME GENDER optional_wimbledon optional_australian_open optional_french_open 
	{ 
		$$.wins = $4;
		strcpy($$.name, $<player_name>2);
		strcpy($$.gender, $<gender>3);
	};


optional_wimbledon: 		WIMBLEDON list_of_years {$$ = $2;} 		| %empty {$$ = 0;};
optional_australian_open: 	AUSTRALIAN_OPEN list_of_years {$$ = 0;} | %empty {$$ = 0;};
optional_french_open: 		FRENCH_OPEN list_of_years {$$ = 0;} 	| %empty {$$ = 0;};


list_of_years: list_of_years ',' year_spec 
	{ 
		$$ = $$ + $3;
	};

list_of_years: year_spec {$$ = $1;};


year_spec: YEAR {$$ = 1; } | YEAR '-' YEAR { $$ = years_in_range($<year>1, $<year>3); } ;

%%

int main(int argc, char **argv) {
	extern FILE *yyin;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input-file-name>\n", argv[0]);
		return 1;
	}
	yyin = fopen (argv [1], "r");
	if (yyin == NULL) {
		fprintf(stderr, "failed to open %s\n", argv[1]);
		return 2;
	}
	yyparse();
  
	fclose (yyin);
	return 0;
}

void yyerror(const char *s) {
	extern int linenum;
	fprintf(stderr, "invalid at line %d: %s\n", linenum, s);
}

int years_in_range(int range_start, int range_end) {
	return range_end - range_start + 1;
}
