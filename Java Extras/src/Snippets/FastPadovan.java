package Snippets;


import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.math.BigInteger;

import static java.math.BigInteger.*;
import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * my solution for this kata: 5819f1c3c6ab1b2b28000624
 * <p>
 * <a href="https://en.wikipedia.org/wiki/Padovan_sequence">Padovan_sequence</a>
 * <p>
 * P(n) = P(n-2) + P(n-1)
 * P(0) = P(1) = P(2) = 1
 * <p>
 * Here I implemented the fast algorithm ( O(lgn) to find P(n) )
 * <p>
 * A = &#9( 0 1 0 )<p>
 * &#9( 0 0 1 )<p>
 * &#9( 1 1 0 )<p>
 * <p>
 * A<sup>(n+1)</sup> = &#9( Pn-4 &#9 Pn-2 &#9 Pn-3 )<p>
 * &#9( Pn-3 &#9 Pn-1 &#9 Pn-2 )<p>
 * &#9( Pn-2 &#9 Pn &#9 Pn-1 )<p>
 */
public class FastPadovan {

    public static BigInteger Get(long n) {
        if (n <= 2) return ONE;
        BigInteger[] initial = {
                ZERO, ONE , ZERO,
                ZERO, ZERO, ONE ,
                ONE , ONE , ZERO
        };
        return matrixPow(initial, n)[7]; // 7 is the position of Pn
    }

    private static BigInteger[] matrixPow(BigInteger[] matrix, long n) {
        BigInteger[] result = matrix;
        while (n != 0) {  // Exponentiation by squaring
            if (n % 2 != 0) result = matrixMultiply(result, matrix);
            n /= 2;
            matrix = matrixMultiply(matrix, matrix);
        }
        return result;
    }

    private static BigInteger[] matrixMultiply(BigInteger[] x, BigInteger[] y) {
        return new BigInteger[]{
                multiply(x[0], y[0]).add(multiply(x[1], y[3])).add(multiply(x[2], y[6])),
                multiply(x[0], y[1]).add(multiply(x[1], y[4])).add(multiply(x[2], y[7])),
                multiply(x[0], y[2]).add(multiply(x[1], y[5])).add(multiply(x[2], y[8])),
                multiply(x[3], y[0]).add(multiply(x[4], y[3])).add(multiply(x[5], y[6])),
                multiply(x[3], y[1]).add(multiply(x[4], y[4])).add(multiply(x[5], y[7])),
                multiply(x[3], y[2]).add(multiply(x[4], y[5])).add(multiply(x[5], y[8])),
                multiply(x[6], y[0]).add(multiply(x[7], y[3])).add(multiply(x[8], y[6])),
                multiply(x[6], y[1]).add(multiply(x[7], y[4])).add(multiply(x[8], y[7])),
                multiply(x[6], y[2]).add(multiply(x[7], y[5])).add(multiply(x[8], y[8]))
        };
    }

    private static BigInteger multiply(BigInteger x, BigInteger y) {
        return x.multiply(y);
    }


    // ~~~~~ Testing ~~~~~~

    @Test
    public void ValueTest1() {
        assertEquals(new BigInteger("1"), Get(1));
        assertEquals(new BigInteger("1"), Get(2));
        assertEquals(new BigInteger("2"), Get(3));
        assertEquals(new BigInteger("2"), Get(4));
    }

    @Test
    public void ValueTest() {
        assertEquals(new BigInteger("1177482265857"), Get(100));
    }

    @Timeout(3)
    @Test
    public void performanceTest() {
         Get(1000000);
    }
}
