package Streams;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import static java.lang.System.out;
import static java.util.function.Function.identity;

public class JavaStreams {
    static String path = Paths.get("").toAbsolutePath() + "/Java Extras/src/Streams";

    public static void main(String[] args) throws IOException {
        out.println("\n1. Integer Stream");
        IntStream
                .range(1, 10)
                .forEach(out::print);
        out.println();

        out.println("\n2. Integer Stream with skip");
        IntStream
                .range(1, 10)
                .skip(5)
                .forEach(out::println);

        out.println("\n3. Integer Stream with sum");
        out.println(
                IntStream
                        .range(1, 5)
                        .sum());

        out.println("\n4. Stream.of, sorted and findFirst");
        Stream.of("Ava", "Aneri", "Alberto")
                .sorted()
                .findFirst()
                .ifPresent(out::println);

        out.println("\n5. Stream from Array, sort, filter and print");
        String[] names = { "Al", "Ankit", "Kushal", "Brent", "Sarika", "amanda", "Hans", "Shivika", "Sarah" };
        Arrays.stream(names)    // same as Stream.of(names)
                .filter(x -> x.startsWith("S"))
                .sorted()
                .forEach(out::println);

        out.println("\n6. average of squares of an int array");
        Arrays.stream(new int[]{ 2, 4, 6, 8, 10 })
                .map(x -> x * x)
                .average()
                .ifPresent(out::println);

        out.println("\n7. Stream from List, filter and print");
        List<String> people = Arrays.asList("Al", "Ankit", "Brent", "Sarika", "amanda", "Hans", "Shivika", "Sarah");
        people
                .stream()
                .map(String::toLowerCase)
                .filter(x -> x.startsWith("a"))
                .forEach(out::println);

        out.println("\n8. Stream rows from text file, sort, filter, and print");
        Stream<String> bands = Files.lines(Paths.get(path + "/bands.txt"));
        bands
                .sorted()
                .filter(x -> x.length() > 13)
                .forEach(out::println);
        bands.close();

        out.println("\n9. Stream rows from text file and save to List");
        List<String> bands2;
        try (Stream<String> lines = Files.lines(Paths.get(path + "/bands.txt"))) {
            bands2 = lines
                    .filter(x -> x.contains("jit"))
                    .collect(Collectors.toList());
        }
        bands2.forEach(out::println);

        out.println("\n10. Stream rows from CSV file and count");
        Stream<String> rows1 = Files.lines(Paths.get(path + "/data.txt"));
        int rowCount = (int) rows1
                .map(x -> x.split(","))
                .filter(x -> x.length == 3)
                .count();
        out.println(rowCount + " rows.");
        rows1.close();

        out.println("\n11. Stream rows from CSV file, parse data from rows");
        Stream<String> rows2 = Files.lines(Paths.get(path + "/data.txt"));
        rows2
                .map(x -> x.split(","))
                .filter(x -> x.length == 3)
                .filter(x -> Integer.parseInt(x[1]) > 15)
                .forEach(x -> out.println(x[0] + "  " + x[1] + "  " + x[2]));
        rows2.close();

        out.println("\n12. Stream rows from CSV file, store fields in HashMap");
        Stream<String> rows3 = Files.lines(Paths.get(path + "/data.txt"));
        Map<String, Integer> map = rows3
                .map(x -> x.split(","))
                .filter(x -> x.length == 3)
                .filter(x -> Integer.parseInt(x[1]) > 15)
                .collect(Collectors.toMap(
                        x -> x[0],
                        x -> Integer.parseInt(x[1])));
        rows3.close();
        for (String key : map.keySet()) {
            out.println(key + "  " + map.get(key));
        }

        out.println("\n13. Reduction - sum");
        double total = Stream.of(999.1, 999.1, 999.1, 1.0, 1.0, 1.0)
                .reduce(0.0, (Double a, Double b) -> b % 1 == 0 ? a + b : a + b % 1);
//                .reduce(0.0, Double::sum);

        out.println("Total = " + String.format("%.2f", total));

        out.println("\n14. Reduction - summary statistics");
        IntSummaryStatistics summary = IntStream.of(7, 2, 19, 88, 73, 4, 10)
                .summaryStatistics();
        out.println(summary);

        List<String> words = Arrays.asList("The", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog");

        out.println("\n15. toMap(..)");
        Map<String, Integer> lengths = words.stream()
                .collect(Collectors.toMap(identity(), String::length));
        out.println(lengths);

        out.println("\n16. toSet(..)");
        Set<Integer> unique = Stream.of(5, 1, 2, 3, 4, 5, 4, 3, 2, 1)
                .collect(Collectors.toSet());
        out.println(unique);

        out.println("\n17. flatMap(..)");
        List<Character> chars = words.stream()
                .flatMap(w -> w.chars().mapToObj(c -> (char) c))
                .collect(Collectors.toList());
        out.println(chars);

        out.println("\n17.b flatMap(..) + toCollection(..)");
        Set<Integer> primeFactors = Arrays.stream(new int[]{ 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 })
                .mapToObj(JavaStreams::primeFactors)
                .flatMap(Set::stream)
                .collect(Collectors.toCollection(TreeSet::new));
        out.println(primeFactors);

        out.println("\n18. groupingBy(..)");
        Map<Integer, List<String>> wordsByLength = words.stream()
                .collect(Collectors.groupingBy(String::length));
        System.out.println(wordsByLength);

        out.println("\n19. groupingBy(..) - counting frequencies");
        int[] numbersGB = new int[]{ 11, 12, 13, 12, 13, 13 };
        Map<Integer, Long> numsByFreq = Arrays.stream(numbersGB)
                .boxed()
                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
        out.println(numsByFreq);

    }

    public static Set<Integer> primeFactors(int n) {
        Set<Integer> result = new HashSet<>();
        while (n % 2 == 0) {
            result.add(2);
            n /= 2;
        }

        // n must be odd at this point.  So we can
        // skip one element (Note i = i +2)
        for (int i = 3; i <= Math.sqrt(n); i += 2) {
            // While i divides n, get i and divide n
            while (n % i == 0) {
                result.add(i);
                n /= i;
            }
        }

        // This condition is to handle the case when
        // n is a prime number greater than 2
        if (n > 2) result.add(n);
        return result;
    }
}
