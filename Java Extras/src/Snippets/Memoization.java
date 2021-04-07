package Snippets;

import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;

public class Memoization {
    static Map<Integer, BigInteger> fibCache = new HashMap<>();

    static BigInteger fib(Integer n) {
        if (n < 0) throw new IllegalArgumentException("n can't be negative");

        if (fibCache.containsKey(n)) {
            System.out.println("found value for " + n + ": " + fibCache.get(n));
            return fibCache.get(n);
        }


        BigInteger value;
        if (n == 0)
            value = BigInteger.ZERO;
        else if (n == 1 || n == 2)
            value = BigInteger.valueOf(1);
        else {
            System.out.println("not found value for " + n + ", computing f(" + (n - 1) + ") + f(" + (n - 2) + ")");
            value = fib(n - 1).add(fib(n - 2));
        }

        fibCache.put(n, value);
        return value;
    }

    public static void main(String[] args) {
        System.out.println("400 => " + fib(400));
    }
}
