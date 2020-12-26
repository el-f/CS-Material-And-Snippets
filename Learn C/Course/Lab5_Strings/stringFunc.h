/*
 * stringFunc.h
 *
 *  Created on: Oct 21, 2018
 *      Author: efrath
 */

#ifndef STRINGFUNC_H_
#define STRINGFUNC_H_

#define MAX_LENGTH  101

int countCapitalLetters(const char *str);

int mostCapitalCountWord(const char *str, char *theWord);

void fixString(char *str);

void arrOfStrings(char *mat, int rows, int cols);

int countWords(char *str);

char *myGets(char *buf, size_t size);


#endif /* STRINGFUNC_H_ */
