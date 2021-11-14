#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "q3.h"

#define FILE_NAME "accounts_comp.bin"
//#define FILE_NAME "accounts.bin"

void Q3() {
    int count;

    AccountInfo *arr = createAccountArrFromFile(FILE_NAME, &count);
    if (arr == NULL) {
        puts("read error");
        return;
    }
    printf("\n\n--------- after read ----------\n\n");
    printAcountInfoArr(arr, count);

    free(arr);
}

AccountInfo *createAccountArrFromFile(const char *fileName, int *pCount) {
    FILE *fp;
    fp = fopen(fileName, "rb");
    if (fp == NULL) return NULL;
    BYTE count;
    if (fread(&count, sizeof(BYTE), 1, fp) != 1) return NULL;
    *pCount = (int) count;
    AccountInfo *arr = calloc(*pCount, sizeof(AccountInfo));
    if (!arr) return NULL;

    for (int i = 0; i < *pCount; i++) {
        if (!createAccountFromFile(fp, &arr[i])) return NULL;
    }
    fclose(fp);
    return arr;
}

int createAccountFromFile(FILE *fp, AccountInfo *accountInfo) {
    BYTE data[3];
    if (fread(&data, sizeof(BYTE), 3, fp) != 3) {
        puts("Error reading account!");
        fclose(fp);
        return 0;
    }
    accountInfo->bankCode = (data[0] >> 5) & 7;
    accountInfo->branch = ((data[0] & 0x1f) << 4) | (data[1] >> 4) & 0xf;
    accountInfo->number = ((data[1] & 0xf) << 8) | data[2];
    return 1;
}

void printAcountInfo(const AccountInfo *pInfo) {
    printf("Account: bank %d branch %d number %d\n", pInfo->bankCode, pInfo->branch, pInfo->number);
}

void printAcountInfoArr(const AccountInfo *arr, int count) {
    printf("There are %d accounts\n", count);
    for (int i = 0; i < count; i++)
        printAcountInfo(&arr[i]);
    printf("\n");
}