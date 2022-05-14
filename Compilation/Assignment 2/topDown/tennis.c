#include <stdio.h>
#include <stdlib.h>  /* for exit() */
#include <string.h>
#include "tennis.h"

extern enum token yylex(void);

enum token lookahead;

void start();

Player player_list();

Player player(Player *);

void match(int expected_token) {
    if (lookahead == expected_token) {
        lookahead = yylex();
    } else {
        char err[100];
        sprintf(err, "error: expected token %s, found token %s",
                token_name(expected_token), token_name(lookahead));
        error_msg(err);
        exit(1);
    }
}

void parse() {
    lookahead = yylex();
    start();
    if (lookahead != $EOF) {
        error_msg("EOF expected");
        exit(1);
    }
}

void start() {
    match(TITLE);
    Player best_woman_in_wimbledon = player_list();

    if (best_woman_in_wimbledon.wins == -1) {
        puts("Did not find a woman player!");
    } else {
        printf("Woman with greatest number of wins at Wimbledon: %s (%d wins)\n",
               best_woman_in_wimbledon.name,
               best_woman_in_wimbledon.wins);
    }
}

Player player_list() {
    Player best_woman_in_wimbledon = {"", "", -1};
    while (lookahead == NAME) {
        match(NAME);
        Player curr = {"", "", -1};
        strcpy(curr.name, lex_val.player_name);
        curr = player(&curr);
        if (strcmp(curr.gender, "Woman") == 0) { // only check women
            best_woman_in_wimbledon = best_woman_in_wimbledon.wins >= curr.wins ? best_woman_in_wimbledon : curr; // get max
        }
    }
    return best_woman_in_wimbledon;
}

Player player(Player *p) {
    int wins = 0;
    strcpy(p->name, lex_val.player_name);
    match(PLAYER_NAME);
    strcpy(p->gender, strcmp(lex_val.gender, "<Man>") ? "Woman" : "Man");
    match(GENDER);

    if (lookahead == WIMBLEDON) { // only count Wimbledon wins
        match(WIMBLEDON);
        wins = 0;
        int last_year;
        while (lookahead == YEAR) {
            last_year = lex_val.year;
            match(YEAR);
            wins++;
            if (lookahead == '-') {
                match('-');
                wins += lex_val.year - last_year; // win in each year in range. (+1 already counted when matched last_year)
                match(YEAR);
            }
            if (lookahead == ',') {
                match(',');
            }
        }
    }
    p->wins = wins;
    optional_competition(AUSTRALIAN_OPEN);
    optional_competition(FRENCH_OPEN);

    return *p;
}

void optional_competition(enum token token) {
    if (lookahead == token) {
        match(token);
        while (lookahead == YEAR) {
            match(YEAR);
            if (lookahead == '-') {
                match('-');
                match(YEAR);
            }
            if (lookahead == ',') {
                match(',');
            }
        }
    }
}

void error_msg(const char *s) {
    extern int yylineno;
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    extern FILE *yyin;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file-name>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        fprintf(stderr, "failed to open %s\n", argv[1]);
        return 2;
    }

    parse();

    fclose(yyin);
    return 0;
}
