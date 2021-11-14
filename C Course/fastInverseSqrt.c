#include <stdio.h>
#include <math.h>

#define ACCURACY_ITERATIONS 1

/*
 *  Cool inverse square root algorithm,
 *  originally authored by John Cramack for the game Quake III.
 *  Fully explained here: https://www.youtube.com/watch?v=p8u_k2LIZyo
 */

float fastInverseSQRT(float num) {
    const float threeHalves = 1.5F;

    float x2 = num * 0.5F;
    float y = num;
    long i = *(long *) &y;                      // evil floating point bit hack

    i = 0x5f3759df - (i >> 1);                  // what the fuck?
    y = *(float *) &i;

    for (i = 0; i < ACCURACY_ITERATIONS; i++) { // here iteration improves accuracy but one is enough
        y *= (threeHalves - (x2 * y * y));
    }

    return y;
}

int main() {
    for (int i = 1; i <= 10; i++)
        printf("%f =? %f\n", fastInverseSQRT((float) i), (1 / sqrt(i)));
}