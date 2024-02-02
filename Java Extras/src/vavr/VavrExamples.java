package vavr;

import io.vavr.collection.*;
import io.vavr.control.*;
import io.vavr.*;

import static io.vavr.Predicates.*;
import static io.vavr.API.*;

import lombok.Data;

@Data
class Person {
    final String name;
    final int age;
}

class PersonValidator {
    private static final String NAME_ERR = "Invalid characters in name: ";
    private static final String AGE_ERR = "Age must be at least 0";

    Validation<Seq<String>, Person> validatePerson(String name, int age) {
        return Validation.combine(validateName(name), validateAge(age)).ap(Person::new);
    }

    private Validation<String, String> validateName(String name) {
        String invalidChars = name.replaceAll("[a-zA-Z ]", "");
        return invalidChars.isEmpty() ? Validation.valid(name) : Validation.invalid(NAME_ERR + invalidChars);
    }

    private Validation<String, Integer> validateAge(int age) {
        return age < 0 ? Validation.invalid(AGE_ERR) : Validation.valid(age);
    }
}


public class VavrExamples {

    public static void main(String[] args) {
        // Example 1: Immutable Collections
        // Using Vavr's List, which is immutable and provides a rich API for functional programming
        List<Integer> list = List.of(1, 2, 3);
        System.out.println("Original List: " + list);
        List<Integer> updatedList = list.map(i -> i * 2); // Returns a new List, original remains unchanged
        System.out.println("Updated List: " + updatedList);

        // Example 2: Option Type
        // Option is a better alternative to null, preventing NullPointerException
        Option<String> maybeString = Option.of("Vavr");
        String result = maybeString.getOrElse("Default"); // Use 'getOrElse' to provide a fallback value
        System.out.println("Option Result: " + result);

        // Example 3: Try for Exception Handling
        // Try is a monadic container type for handling exceptions in a functional way
        for (Object o : List.of("42", "not a number")) {
            String value = o.toString();
            String computationResult = Try.of(() -> riskyComputation(value))
                    .recover(NumberFormatException.class, "Recovery value")
                    .getOrElse("Default");
            System.out.println("Try Result: " + computationResult);
        }

        // Example 4: Pattern Matching (like switch-case but more powerful)
        // Vavr provides a rich API for pattern matching, much more expressive than Java's switch-case
        String matchResult = Match(1).of(
                Case($(1), "One"),
                Case($(2), "Two"),
                Case($(), "?")
        );
        System.out.println("Match Result: " + matchResult);

        // Example 5: Functional Data Structures
        // Immutable Map example, showcasing how Vavr enables functional programming with immutable collections
        Map<Integer, String> map = Map(1, "One", 2, "Two");
        Map<Integer, String> updatedMap = map.put(3, "Three");
        System.out.println("Original Map: " + map);
        System.out.println("Updated Map: " + updatedMap);
        System.out.println("get 1: " + updatedMap.get(1).getOrNull());


        Person person = new Person("John", 30);

        String greeting = Match(person).of(
                Case($(p -> p.age < 18), "You're too young to enter."),
                Case($(p -> p.age >= 18 && p.age < 65), p -> "Welcome, " + p.name + "!"),
                Case($(), "You're wise beyond measure.")
        );

        System.out.println(greeting);

        for (int mark : List.of(90, 50)) {
            String markResult = computeWithEither(mark).fold(
                    l -> "Bad Mark: " + l,
                    r -> "Passed: " + r
            );
            System.out.println(markResult);
        }


        // Advanced Immutable Collections
        advancedCollections();

        // Functional Interfaces and High-Order Functions
        functionalInterfaces();

        // Advanced Error Handling with Try
        advancedErrorHandling();

        // Pattern Matching and Decomposition
        patternMatching();

        // Lazy Computations
        lazyComputations();


        // Validation
        PersonValidator validator = new PersonValidator();
        Validation<Seq<String>, Person> validResult = validator.validatePerson("John", 30);
        System.out.println(validResult);
        System.out.println(validResult.isValid());
        System.out.println(validResult.get());

        Validation<Seq<String>, Person> invalidResult = validator.validatePerson("John1", -1);
        System.out.println(invalidResult);
        System.out.println(invalidResult.isInvalid());
        System.out.println(invalidResult.getError());

        // how to deal with unknown result in production:
        // if (validResult.isInvalid()) {
        //     throw new IllegalArgumentException("Invalid person: " + invalidResult.getError());
        // }
    }

    private static void advancedCollections() {
        // Creating more complex immutable collections
        Map<Integer, List<String>> complexMap = HashMap.of(
                1, List.of("Java", "Vavr"),
                2, List.of("Functional", "Programming")
        );

        // Using flatMap, filter, and other higher-order functions
        List<String> filteredList = complexMap
                .flatMap(t -> t._2) // Flatten the structure
                .filter(s -> s.contains("r")) // Filter by string length
                .toList(); // Convert to List

        System.out.println("Filtered and Flattened List: " + filteredList);
    }

    private static void functionalInterfaces() {
        // Vavr enhances functional programming with its functional interfaces
        Function2<Integer, Integer, Integer> sum = Integer::sum;
        int result = sum.apply(1, 2); // Functional interface for a function taking 2 arguments
        System.out.println("Sum: " + result);

        // Currying
        Function1<Integer, Function1<Integer, Integer>> curriedSum = sum.curried();
        int curriedResult = curriedSum.apply(1).apply(2);
        System.out.println("Curried Sum: " + curriedResult);
    }

    private static void advancedErrorHandling() {
        // More complex error handling scenarios with Try
        Try<Integer> computation = Try.of(() -> riskyComputation("Not a number"))
                .mapTry(Integer::parseInt) // Try to parse the result, mapTry for handling checked exceptions
                .recover(NumberFormatException.class, -1); // Provide a recovery value

        System.out.println("Advanced Error Handling Result: " + computation.getOrElse(-999));
    }

    private static void patternMatching() {
        // More complex pattern matching, including type and condition checks
        Object obj = "Test String";
        String matchResult = Match(obj).of(
                Case($(instanceOf(String.class).and(s -> s.startsWith("Test"))), "String starts with 'Test'"),
                Case($(), "Unknown")
        );

        System.out.println("Pattern Matching Result: " + matchResult);
    }

    private static void lazyComputations() {
        // Lazy computation with Lazy type, which computes its value on the first call and remembers the result
        Lazy<Double> lazyValue = Lazy.of(Math::random);
        System.out.println("Lazy Value (first call): " + lazyValue.get());
        System.out.println("Lazy Value (second call): " + lazyValue.get()); // Same value as first call
    }

    static Either<String, Integer> computeWithEither(int mark) {
        return mark < 85
                ? Either.left("Marks not acceptable (" + mark + ")")
                : Either.right(mark);
    }

    // Example of a method that might throw an exception, used with Try
    private static String riskyComputation(String input) {
        return "Computed " + Integer.parseInt(input);
    }
}
