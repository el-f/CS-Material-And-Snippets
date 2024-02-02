package vavr;

import io.vavr.collection.Stream;

import java.util.*;

public class Streams {

    static int[] intArray = new int[]{1, 2, 4};
    static List<Integer> intList = new ArrayList<>();

    public static void main(String[] args) {
        vavrStreamElementAccess();
        System.out.println("#####################################\n");
        vavrParallelStreamAccess();
        System.out.println("#####################################\n");
        vavrStreamManipulation();
        System.out.println("#####################################\n");
        vavrStreamDistinct();
    }

    public static void vavrStreamElementAccess() {
        System.out.println("Vavr Element Access");
        System.out.println("====================================");
        Stream<Integer> vavredStream = Stream.ofAll(intArray);
        System.out.println("Vavr index access: " + vavredStream.get(2));
        System.out.println("Vavr head element access: " + vavredStream.get());

        Stream<String> vavredStringStream = Stream.of("foo", "bar", "baz");
        System.out.println("Find foo " + vavredStringStream.indexOf("foo"));
    }

    public static void vavrParallelStreamAccess() {
        try {
            System.out.println("Vavr Stream Concurrent Modification");
            System.out.println("====================================");
            Stream<Integer> vavrStream = Stream.ofAll(intList);
            intList.add(1);
            vavrStream.forEach(i -> System.out.println("in a Vavr Stream: " + i));
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        Stream<Integer> wrapped = Stream.ofAll(intArray);
        intArray[2] = 5;
        wrapped.forEach(i -> System.out.println("Vavr looped " + i));
    }

    public static void vavrStreamManipulation() {
        System.out.println("Vavr Stream Manipulation");
        System.out.println("====================================");
        List<String> stringList = new ArrayList<>();
        stringList.add("foo");
        stringList.add("bar");
        stringList.add("baz");
        Stream<String> vavredStream = Stream.ofAll(stringList);
        System.out.println("Vavr Stream: " + vavredStream.mkString(", "));

        Stream<String> vavredStream2 = vavredStream.insert(2, "buzz");
        System.out.println("Vavr Stream item after stream addition: " + vavredStream2.mkString(", "));
        System.out.println("List item after stream addition: " + stringList);

        Stream<String> deletionStream = vavredStream.remove("bar");
        System.out.println("Vavr Stream item after stream deletion: " + deletionStream.mkString(", "));

        stringList.add("new-item-in-list");
        System.out.println("List item after stream deletion: " + stringList);
    }

    public static void vavrStreamDistinct() {
        Stream<String> vavredStream = Stream.of("foo", "bar", "baz", "buxx", "bar", "bar", "foo");
        Stream<String> distinctVavrStream = vavredStream.distinctBy(String::compareTo);
        System.out.println("Vavr Stream after distinct operation: " + distinctVavrStream.mkString(", "));
    }

}