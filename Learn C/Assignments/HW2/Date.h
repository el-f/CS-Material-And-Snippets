#ifndef DATE
#define DATE

typedef struct {
    int day;
    int month;
    int year;
} Date;

Date initDate();

int getValidHour();

int isValidDate(int day, int month, int year);

#endif //DATE
