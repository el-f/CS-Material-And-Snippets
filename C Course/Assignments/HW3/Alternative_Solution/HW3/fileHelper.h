#pragma once

int	 writeStringToFile(char* str, FILE* fp,const char* msg);
int	 writeCharsToFile(char* arr,int size, FILE* fp, const char* msg);
int	 writeIntToFile(int val, FILE* fp, const char* msg);

char* readStringFromFile(FILE* fp,const char* msg);
int	 readCharsFromFile(char* arr, int size, FILE* fp, const char* msg);
int	  readIntFromFile(int* val, FILE* fp, const char* msg);