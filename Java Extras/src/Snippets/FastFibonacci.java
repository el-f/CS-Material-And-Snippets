package Snippets;

import java.math.BigInteger;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

import static java.math.BigInteger.*;

// my solution for this kata: 53d40c1e2f13e331fc000c26
public class FastFibonacci {

    static final BigInteger TWO = valueOf(2);

    static BigInteger fib(BigInteger n) {
        BigInteger[] initial = {
                ONE, ONE,
                ONE, ZERO
        };
        BigInteger result = matrixPow(initial, n)[1].abs();
        if (n.compareTo(ZERO) < 0) return result.multiply(BigInteger.valueOf((long) Math.pow(1, n.longValue() + 1)));
        return result;
    }

    private static BigInteger[] matrixPow(BigInteger[] mat, BigInteger n) {
        BigInteger[] result = {
                ONE, ZERO,
                ZERO, ONE
        };
        while (!n.equals(ZERO)) {
            if (!n.mod(TWO).equals(ZERO)) result = matMul(result, mat);
            n = n.divide(TWO);
            mat = matMul(mat, mat);
        }
        return result;
    }

    private static BigInteger[] matMul(BigInteger[] a, BigInteger[] b) {
        return new BigInteger[]{
                mul(a[0], b[0]).add(mul(a[1], b[2])), mul(a[0], b[1]).add(mul(a[1], b[3])),
                mul(a[2], b[0]).add(mul(a[3], b[2])), mul(a[2], b[1]).add(mul(a[3], b[3]))
        };
    }

    private static BigInteger mul(BigInteger a, BigInteger b) {
        return a.multiply(b);
    }

    // ------------------------------------------------------------ //

    public static void tests() {
        Set<Long> tests = new HashSet<>();
        tests.add((long) 0);
        tests.add((long) 1);
        tests.add((long) 2);
        tests.add((long) 3);
        tests.add((long) 4);
        tests.add((long) 5);
        tests.add((long) -6);
        tests.add((long) -96);
        tests.add((long) 1000);
        tests.add((long) 1001);
        Random rnd = new Random();
        rnd.longs(10, -100, 0).forEach(tests::add);
        rnd.longs(1, 10000, 100000).forEach(tests::add);
        rnd.longs(1, 1000000, 1500000).forEach(tests::add);
        tests.forEach(test -> System.out.println(fib(BigInteger.valueOf(test))));
    }

    public static void main(String[] args) {
        tests();
    }

}
