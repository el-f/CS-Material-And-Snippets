#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "GeneralBits.h"

void printCharAsBinary(unsigned char ch) {
    int i;
    unsigned char temp;
    for (i = 0; i < 8; i++) {
        temp = ch << i;
        temp = temp >> 7;
        printf("%d", (int) temp);
    }
    printf(" ");
}

// create mask with 1's between left-right (including)
unsigned int createMask(int left, int right) {
    int temp;
    if (left < right) {
        temp = left;
        left = right;
        right = temp;
    }
    return (1 << (left + 1)) - (1 << right);
}

int writeToBinFile(const char *fileName, void *pBuffer, int size) {
    FILE *fp;
    fp = fopen(fileName, "wb");
    if (!fp) return 0;

    fwrite(pBuffer, size, sizeof(char), fp);
    fclose(fp);
    return 1;
}

int readFromBinFile(const char *fileName, void *pBuffer, int size) {
    FILE *fp;
    fp = fopen(fileName, "rb");
    if (!fp) return 0;

    fread(pBuffer, size, sizeof(char), fp);
    fclose(fp);
    return 1;
}

