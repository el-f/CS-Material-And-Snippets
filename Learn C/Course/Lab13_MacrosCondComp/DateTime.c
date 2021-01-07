#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DateTime.h"

void printDate(const Date *pDate) {
#ifdef TO_FILE
    printToFile(pDate,FILE_NAME);
#else
    printToScreen(pDate);
#endif
}

void printToFile(const Date *pDate, const char *fileName) {
    FILE *fp;
    char msg[LEN] = {0};

    fp = fopen(fileName, "w");
    if (!fp)
        return;

    createMsgByCondition(pDate, msg);

    fprintf(fp, "%s\n", msg);
    fclose(fp);
}

void printToScreen(const Date *pDate) {
    char msg[LEN];

    createMsgByCondition(pDate, msg);

    printf("%s\n", msg);
}

void createMsgByCondition(const Date *pDate, char *msg) {
#ifdef MSG_MAX
    createMaxMsg(pDate, msg);
#else
#ifdef MSG_REG
    createRegMsg(pDate, msg);
#else
    createMsg(pDate, msg);
#endif
#endif
}

void createMaxMsg(const Date *pDate, char *msg) {
    createRegMsg(pDate, msg);
    strcat(msg, " ");
    strcat(msg, pDate->sign);
}

void createRegMsg(const Date *pDate, char *msg) {
    char timeMsg[LEN];
    createMsg(pDate, msg);
    createTimeMsg(&pDate->theTime, timeMsg);
    strcat(msg, " ");
    strcat(msg, timeMsg);
}

void createMsg(const Date *pDate, char *msg) {
    sprintf(msg, "D:%u M:%u Y:%u", pDate->day, pDate->month, pDate->year);
}

void createTimeMsg(const Time *pTime, char *msg) {
    sprintf(msg, "%u:%u:%u", pTime->hour, pTime->min, pTime->sec);

}


