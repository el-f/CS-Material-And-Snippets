#ifndef __UTILS__
#define __UTILS__

#include <stdbool.h>

#define ORIGIN "origin"
#define DESTINATION "destination"
#define NO_DIR "an"

#define STR_MAX_LENGTH 256

int scanInt();

char *getStr(char *buf, size_t size);

char *getStrAuto();

void strToUpper(char *str);

void strToLower(char *str);

int isAllLetters(const char *str);

char *getValidIATA(char dir[]);

void trim(char *str);

void capitalizeFirstWords(char *string);

void alternateCapitalization(char *string);

char *doubleSpacesAndAlternateCaps(char *string);

#endif
