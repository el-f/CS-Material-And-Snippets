#include <stdio.h>

/*
 *      return min or max depending on input ( '>' or '<' )
 *      without using 'if' statements
 */


/*
 *  Solution - Elazar Fine - github.com/Elfein7Night
 *
 *          sign | operation | return
 *          -------------------------
 *            0  |     0     |   b
 *            0  |     1     |   a
 *            1  |     0     |   a
 *            1  |     1     |   b
 */
int getMinMax(int a, int b, char c) {
    int operation = (c & 2) >> 1;      // 1: get max, 0: get min
    int sign = !(1 + ((a - b) >> 31));      // 1: a < b, 0: a > b
    int xor = sign ^ operation;
    return xor * a | !xor * b;
}

// Another Solution - Denis Karabitski - github.com/denisaka1
int minMax(int a, int b, char c) {
    int choice = '=' - c;
    int sign = (a - b) >> (sizeof(int) * 8 - 1);
    int abs = ((a - b) + sign) ^ sign;
    return ((a + b) - choice * abs) / 2;
}

/*
 *  Trivial Solution - Elazar Fine - github.com/Elfein7Night
 *
 *          choice | result | return
 *          -------------------------
 *            0  |     0     |   a
 *            0  |     1     |   b
 *            1  |     0     |   b
 *            1  |     1     |   a
 */
int trivialMM(int a, int b, char c) {
    int choice = c == '>';
    int result = a > b;
    int xor = choice ^ result;
    return xor * b + !xor * a;
}