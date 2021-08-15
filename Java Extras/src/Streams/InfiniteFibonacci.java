package Streams;

import java.math.BigInteger;
import java.util.concurrent.atomic.AtomicReference;
import java.util.stream.Stream;

public class InfiniteFibonacci {

    // my solution for this kata: 55695bc4f75bbaea5100016b (a bit enhanced for accuray)

    public static Stream<BigInteger> generateFibonacciSequence() {
        AtomicReference<BigInteger> lastHolder = new AtomicReference<>(BigInteger.valueOf(1));
        return Stream.iterate(BigInteger.ONE, x -> x.add(lastHolder.getAndSet(x)));
    }

    public static void main(String[] args) {
        generateFibonacciSequence()
                .limit(1000)
                .forEach(System.out::println);
    }

}
