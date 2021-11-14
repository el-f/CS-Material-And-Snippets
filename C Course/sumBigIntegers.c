#include <stdlib.h>
#include <string.h>

// sum very big integers as strings

char *strsum(const char *a, const char *b) {
    int a_len, b_len, size, big, index, zero_occ;
    char *result;

    a_len = strlen(a);
    b_len = strlen(b);
    size = (a_len > b_len ? a_len : b_len) + 1;
    result = malloc(size + 1);
    result[size] = 0;
    for (a_len--, b_len--, big = 0, index = size - 1; index > 0; a_len--, b_len--, index--) {
        result[index] = (a_len >= 0 ? a[a_len] : '0') + (b_len < 0 ? '0' : b[b_len]) - '0' + big;
        big = result[index] > '9';
        if (big) result[index] -= 10;
    }
    *result = (char) ('0' + big);
    zero_occ = strspn(result, "0");
    for (index = 0; index <= size - zero_occ; index++) result[index] = result[index + zero_occ];

    // 0 addition edge-case
    if (strlen(result) == 0 && (strlen(a) != 0 || strlen(b)) != 0) { *result = '0'; *(result + 1) = 0; }

    return result;
}