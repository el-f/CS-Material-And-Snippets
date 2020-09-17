#include <stdio.h>

void testFunc(int *p);

int main(int argc, char const *argv[]) {
    int i = 3;
    int *p = &i;
    printf("%d=%d\n", *p, i);
    *p = 5;
    printf("%d=%d\n", *p, i);
    testFunc(p);
    printf("%d=%d\n", *p, i);

    return 0;
}

void testFunc(int *p) {
    *p = 8;
}


