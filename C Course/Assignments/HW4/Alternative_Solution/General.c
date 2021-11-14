#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "General.h"
#include "myMacros.h"


char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\t", msg);
	myGets(temp, MAX_STR_LEN,stdin);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	CHECK_RETURN_NULL(theStr);
	

	strcpy(theStr, str);
	return theStr;
}



char*  myGets(char* buffer, int size, FILE* fp)
{
	if (buffer != NULL && size > 0)
	{
		if (fgets(buffer, size, fp))
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength)
{
	char temp[255];
	char* delimiters = " ";
	char* word;
	int count = 0;

	strcpy(temp, str);
	char** wordsArray = NULL;
	*pTotalLength = 0;

	word = strtok(temp, delimiters);
	while (word != NULL)
	{
		wordsArray = (char**)realloc(wordsArray,(count + 1)*sizeof(char*));
		CHECK_RETRUN_0(wordsArray);
		wordsArray[count] = getDynStr(word);
		count++;
		*pTotalLength += (int)strlen(word);
		word = strtok(NULL, delimiters);
	}
	*pCount = count;
	return wordsArray;
}

void	printStr(const void* str)
{
	puts(str);
}

void	freePtr(void* str)
{
	free(str);
}



void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element))
{
	for (int i = 0; i < size; i++)
		func((char*)(arr)+i*typeSize);

}

char*	catStrings(char* base,char* first, va_list lst)
{
	char* resStr = (char*)malloc( (strlen(base)+1)*sizeof(char));
	if (!resStr)
		return NULL;
	strcpy(resStr, base);
	char* str = first;
	while (str != NULL)
	{
		resStr = (char*)realloc(resStr,(strlen(resStr)+strlen(str)+2) * sizeof(char));
		if (!resStr)
			return NULL;
		strcat(resStr,"_");
		strcat(resStr, str);
		str = va_arg(lst, char*);
	}
	va_end(lst);
	return resStr;
}
