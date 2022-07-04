package Streams;


import java.util.*;

import static java.lang.System.out;
import static java.util.function.UnaryOperator.identity;
import static java.util.stream.Collectors.counting;
import static java.util.stream.Collectors.groupingBy;

//  54bf1c2cd5b56cc47f0007a1
public class DuplicateChars {

    static final boolean PRINT_MAP = false;

    public static void main(String[] args) {
        out.println(duplicateCount("hello world!"));
        out.println(duplicateCount("the quick brown fox jumped over the lazy dog!"));
        out.println(duplicateCount("abcdefghijklmnopqrstuvwxyz"));
    }

    private static Map<Character, Long> charFrequenciesMap(final String text) {
        return text.codePoints()
                .map(Character::toLowerCase)
                .mapToObj(c -> (char) c)
                .collect(groupingBy(identity(), counting()));
    }

    static long duplicateCount(final String text) {
        if (PRINT_MAP) out.println(charFrequenciesMap(text));

        return charFrequenciesMap(text)
                .values().stream()
                .filter(i -> i > 1)
                .count();
    }

}