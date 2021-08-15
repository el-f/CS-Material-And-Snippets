package Snippets;

import java.math.BigInteger;
import java.util.Iterator;
import java.util.PrimitiveIterator;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;

public class InfiniteFibonacci {

    // my solution for this kata: 55695bc4f75bbaea5100016b

    static final AtomicInteger lastHolder = new AtomicInteger(0);

    public static IntStream generateFibonacciSequence() {
        return IntStream.iterate(1, it -> {
            int last = lastHolder.get();
            lastHolder.set(it);
            return it + last;
        });
    }

}
