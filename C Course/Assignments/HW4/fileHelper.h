#pragma once

typedef unsigned char BYTE;

#define COMPRESSED_BINARY_FILE

#define CHECK_0_MSG_CLOSE_FILE(value, fp, msg) if(!(value)) { puts(msg); fclose(fp); return 0;}
#define CHECK_NULL_MSG_CLOSE_FILE(pointer, fp, msg) if(!(pointer)) { puts(msg); fclose(fp); return 0;}
#define MSG_CLOSE_RETURN_0(fp, msg) { puts(msg); fclose(fp); return 0; }

int writeStringToFile(char *str, FILE *fp, const char *msg);

int writeCharsToFile(char *arr, int size, FILE *fp, const char *msg);

int writeIntToFile(int val, FILE *fp, const char *msg);

char *readStringFromFile(FILE *fp, const char *msg);

char *readStringFromCompressedFile(FILE *fp, const char *msg, int strLength);

int readCharsFromFile(char *arr, int size, FILE *fp, const char *msg);

int readIntFromFile(int *val, FILE *fp, const char *msg);