#include <stdio.h>

#include "Date.h"
#include "Utils.h"

Date initDate() {
    int day, month, year;
    char buf[STR_MAX_LENGTH];
    bool validDate = false;
    while (!validDate) {
        printf("Enter date (format: dd/mm/yyyy) (year: 1900-2100):\n");
        if (fgets(buf, STR_MAX_LENGTH, stdin)) {
            if (sscanf(buf, "%d/%d/%d", &day, &month, &year) == 3) {
                validDate = isValidDate(day, month, year);
            } else {
                printf("Please use the correct format!\n");
            }
        }
    }

    Date date = {day, month, year};
    return date;
}

int getValidHour() {
    int hour;
    do {
        printf("Please enter valid hour (0-23):\n");
        hour = scanInt();
    } while (hour < 0 || hour > 23);

    return hour;
}

int isValidDate(int day, int month, int year) {
    //check year
    if (year >= 1900 && year <= 2100) {
        //check month
        if (month >= 1 && month <= 12) {
            //check days
            if (((day >= 1 && day <= 31) &&
                 (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
                || ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11))
                || ((day >= 1 && day <= 28) && (month == 2))
                || ((day == 29 && month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))))) {
                return true;
            } else printf("Invalid Day!\n");
        } else printf("Invalid Month!\n");
    } else printf("Invalid Year!\n");

    return false;
}
