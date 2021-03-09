#include <stdio.h>

/*
 *      return min or max depending on input symbol ( '>' or '<' )
 *      without using 'if' statements
 */

// Mathematical Solution - Denis Karabitski - github.com/denisaka1
int minMax(int a, int b, char symbol) {
    char tempSymbol = '=';
    int result = tempSymbol - symbol;
    return ((a + b) + result * (a - b)) / 2;
}

// Programming Solution - Barak Moskovich - github.com/BarakMoskovich
int veryAnnoyingCalc(int a, int b, char symbol) {
    int arr[] = {a, 0, b};
    return arr[62 - (int) symbol] - ((a - b) & ((a - b) >> (sizeof(int) * 8 - 1)));
}

/*
 *  Brute Force Solution - Elazar Fine - github.com/Elfein7Night
 *
 *          sign | operation | return
 *          -------------------------
 *            0  |     0     |   b
 *            0  |     1     |   a
 *            1  |     0     |   a
 *            1  |     1     |   b
 */
int getMinMax(int a, int b, char symbol) {
    int operation = (symbol & 2) >> 1;      // 1: get max, 0: get min
    int sign = !(1 + ((a - b) >> 31));      // 1: a < b, 0: a > b
    int xor = sign ^ operation;
    return xor * a | !xor * b;
}
