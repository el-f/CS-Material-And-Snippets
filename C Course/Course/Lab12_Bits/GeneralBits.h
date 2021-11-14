#ifndef __GENERAL_BITS__
#define __GENERAL_BITS__

void printCharAsBinary(unsigned char ch);

unsigned int createMask(int left, int right);

int writeToBinFile(const char *fileName, void *pBuffer, int size);

int readFromBinFile(const char *fileName, void *pBuffer, int size);

#endif