package Snippets;

import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.LongStream;

public class InfiniteFibonacci {

    // my solution for this kata: 55695bc4f75bbaea5100016b

    public static LongStream generateFibonacciSequence() {
        AtomicLong lastHolder = new AtomicLong(1);
        return LongStream.iterate(1, it -> lastHolder.getAndIncrement());
    }

}
