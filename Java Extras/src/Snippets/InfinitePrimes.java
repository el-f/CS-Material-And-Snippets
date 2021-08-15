package Snippets;

import java.util.Iterator;
import java.util.stream.IntStream;
import java.util.BitSet;

// my solution for this kata: 59122604e5bc240817000016
public class InfinitePrimes {

    static BitSet sieve;

    static boolean first = true;

    public static IntStream stream() {
        if (first) {
            int window = (int) 1E9;
            sieve = new BitSet(window);
            sieve.flip(2, window - 1);

            for (int i = sieve.nextSetBit(2); 0 < i && i < 31622; i = sieve.nextSetBit(i + 1)) {
                for (int j = 2 * i; j < window; j += i) {
                    sieve.clear(j);
                }
            }
            first = false;
        }

        return IntStream.iterate(2, i -> sieve.nextSetBit(i + 1));
    }

    public static void main(String[] args) {
        int printEvery = (int) 1E6;
        Iterator<Integer> it = stream().iterator();
        for (int i = 0; i < 1E9; i++) {
            if (i % printEvery == 0) {
                System.out.println(it.next());
            } else it.next();
        }
    }
}