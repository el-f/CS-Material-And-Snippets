#include <stdio.h>
#include <stdlib.h>

#include "Date.h"
#include "GeneralBits.h"


unsigned char *compressedDate(const Date *pDate) {
    char *buffer = (char *) calloc(SIZE, sizeof(char));
    if (!buffer) return NULL;

    buffer[0] = pDate->day | pDate->month << 5;
    buffer[1] = pDate->month >> 3 | pDate->year << 1;
    buffer[2] = pDate->year >> 7;

    return buffer;
}

void unCompressedDate(unsigned char *pBuffer, Date *pDate) {
    pDate->day = pBuffer[0] & 0x1f;
    pDate->month = pBuffer[0] >> 5 | (pBuffer[1] & 0x1) << 3;
    pDate->year = pBuffer[1] >> 1 | (pBuffer[2] & 0xf) << 7;
}
