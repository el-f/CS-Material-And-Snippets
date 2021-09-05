package Streams;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;
import java.util.BitSet;

// my solution for this kata: 59122604e5bc240817000016
public class InfinitePrimes {

    static BitSet sieve;

    static {
        int window = (int) 1E9;
        sieve = new BitSet(window);
        sieve.flip(2, window - 1);

        for (int i = sieve.nextSetBit(2); 0 < i && i < 31622; i = sieve.nextSetBit(i + 1)) {
            for (int j = 2 * i; j < window; j += i) {
                sieve.clear(j);
            }
        }
    }

    public static IntStream streamPrimes() {
        return IntStream.iterate(2, i -> sieve.nextSetBit(i + 1))
                .limit(sieve.cardinality());
    }

    public static void main(String[] args) {
        AtomicInteger printIndex = new AtomicInteger(0);
        System.out.println(sieve.cardinality() + " primes in range of 0 - 1E9");
        System.out.println("10 samples of primes in that range:");
        streamPrimes()
                .forEach(x -> {
                    if (printIndex.getAndIncrement() % 5E6 == 0){
                        System.out.println(x);
                    }
                });
    }
}