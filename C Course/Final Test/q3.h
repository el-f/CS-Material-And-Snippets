#pragma once

typedef unsigned char BYTE;

typedef struct {
    int bankCode;
    int branch;
    int number;
} AccountInfo;


void Q3();

AccountInfo *createAccountArrFromFile(const char *fileName, int *pCount);

int createAccountFromFile(FILE *fp, AccountInfo *accountInfo);

void printAcountInfo(const AccountInfo *pInfo);

void printAcountInfoArr(const AccountInfo *arr, int count);


