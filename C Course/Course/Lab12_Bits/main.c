#include <stdio.h>
#include <stdlib.h>

#include "Date.h"
#include "GeneralBits.h"

#define FILE_NAME "date.bin"

int main() {
    int i;
    unsigned char *dateCompressed;
    Date origDate = {7, 2, 2010}, newDate;
    unsigned char buffer[SIZE]; // for read!
    dateCompressed = compressedDate(&origDate);
    if (!dateCompressed)
        return -1;

    printf("The compressed data:\n");
    for (i = SIZE - 1; i >= 0; i--)
        printCharAsBinary(dateCompressed[i]);

    if (!writeToBinFile(FILE_NAME, dateCompressed, SIZE))
        return -2;

    free(dateCompressed);

    if (!readFromBinFile(FILE_NAME, buffer, SIZE))
        return -3;

    unCompressedDate(buffer, &newDate);

    printf("\nThe read date is %d/%d/%d\n",
           newDate.day, newDate.month, newDate.year);

    system("pause");
    return 1;
}
