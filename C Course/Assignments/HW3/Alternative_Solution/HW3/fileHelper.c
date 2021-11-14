#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileHelper.h"
#include "General.h"


int	 writeStringToFile(char* str, FILE* fp,const char* msg)
{
	int length = strlen(str);
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
	{
		puts(msg);
		fclose(fp);
		return 0;
	}
	return 1;

}

int	 writeIntToFile(int val, FILE* fp, const char* msg)
{
	if (fwrite(&val, sizeof(int), 1, fp) != 1)
	{
		puts(msg);
		fclose(fp);
		return 0;
	}
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
	{
		puts(msg);
		fclose(fp);
		return NULL;
	}
	if (fread(str, sizeof(char), length, fp) != length)
	{
		puts(msg);
		fclose(fp);
		return NULL;
	}
	return str;

}

int	 readCharsFromFile(char* arr, int length, FILE* fp, const char* msg)
{
	if (fread(arr, sizeof(char), length, fp) != length)
	{
		puts(msg);
		fclose(fp);
		return 0;
	}
	return 1;
}

int	  readIntFromFile(int* pVal, FILE* fp, const char* msg)
{
	if (fread(pVal, sizeof(int), 1, fp) != 1)
	{
		puts(msg);
		fclose(fp);
		return 0;
	}
	return 1;

}