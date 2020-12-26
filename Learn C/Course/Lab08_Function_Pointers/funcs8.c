//
// Created by Elazar on 08/12/2020.
//
#include <ctype.h>
#include <string.h>
#include "funcs8.h"

size_t sum(const char *str, size_t (*getSum)(const char *)) {
    return getSum(str);
}

size_t getAsciiSum(const char *str) {
    int sum = 0;
    for (int i = 0; i < strlen(str); ++i) {
        sum += *(str + i);
    }
    return sum;
}
