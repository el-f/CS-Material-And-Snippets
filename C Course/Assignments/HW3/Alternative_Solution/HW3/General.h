#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255


char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size, FILE* fp);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str,int* pCount,int* pTotalLength);
void	printStr(const void* str);
void	freePtr(void* str);
void	generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));



#endif

