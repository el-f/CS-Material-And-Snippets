#ifndef TENNIS
#define $EOF 0

enum token {
     // EOF = 0,
     TITLE = 1,
     NAME,
     PLAYER_NAME,
     GENDER,
     YEAR,
     WIMBLEDON,
     FRENCH_OPEN,
     AUSTRALIAN_OPEN
	 // ',', '-' : given as (as specified in the grammar)

};

typedef struct {
    char    name[80];
    char    gender[10];
    int     wins;
} Player;

union _lval {
    char    player_name[80];
    char    gender[10];
    int     year;
};

extern union _lval lex_val; // yylval replacement

char*   token_name(enum token);
void    error_msg(const char *);
void    optional_competition(enum token);

#endif // TENNIS
