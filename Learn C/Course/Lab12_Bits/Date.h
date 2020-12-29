#ifndef __MY_DATE__
#define __MY_DATE__

#define SIZE 3

typedef struct {
    unsigned int day;  //1->31
    unsigned int month;//1->12
    unsigned int year; //0 - 2047

} Date;

unsigned char *compressedDate(const Date *date);

void unCompressedDate(unsigned char *pBuffer, Date *date);


#endif