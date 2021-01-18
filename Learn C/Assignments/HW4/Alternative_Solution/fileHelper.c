#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileHelper.h"
#include "General.h"
#include "myMacros.h"


int	 writeStringToFile(char* str, FILE* fp,const char* msg)
{
	int length = (int)strlen(str);
	length++;
	if (!writeIntToFile(length, fp,msg))
		return 0;
	
	if (!writeCharsToFile(str, length, fp, msg))
		return 0;


	return 1;
}

int	 writeCharsToFile(char* arr, int size, FILE* fp, const char* msg)
{
	if (fwrite(arr, sizeof(char), size, fp) != size)
		MSG_CLOSE_RETURN_0(fp, msg);
	return 1;
}

int	 writeIntToFile(int val, FILE* fp, const char* msg)
{
	if (fwrite(&val, sizeof(int), 1, fp) != 1)
		MSG_CLOSE_RETURN_0(fp, msg);

	return 1;
}

char* readStringFromFile(FILE* fp, const char* msg)
{
	char* str;
	int length;
	if (!readIntFromFile(&length, fp,msg))
		return NULL;
	str = (char*)malloc((length) * sizeof(char));
	if (!str)
		MSG_CLOSE_RETURN_NULL(fp, msg);

	if (fread(str, sizeof(char), length, fp) != length)
		MSG_CLOSE_RETURN_NULL(fp, msg);

	return str;

}

int	 readCharsFromFile(char* arr, int length, FILE* fp, const char* msg)
{
	if (fread(arr, sizeof(char), length, fp) != length)
		MSG_CLOSE_RETURN_0(fp, msg);
	
	return 1;
}

int	  readIntFromFile(int* pVal, FILE* fp, const char* msg)
{
	if (fread(pVal, sizeof(int), 1, fp) != 1)
		MSG_CLOSE_RETURN_0(fp, msg);

	return 1;

}