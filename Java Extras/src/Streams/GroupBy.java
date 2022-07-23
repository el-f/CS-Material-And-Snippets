package Streams;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.*;
import java.util.stream.*;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static Streams.GroupBy.*;
import static org.junit.jupiter.api.Assertions.assertEquals;

// examples of grouping data using streams
public class GroupBy {

    public static Map<String, Double> getAverageGradeByDepartment(Stream<Student> students) {
        return students.collect(Collectors.groupingBy(Student::getDepartment, Collectors.averagingDouble(Student::getGrade)));
    }

    public static Map<String, Long> getNumberOfStudentsByDepartment(Stream<Student> students) {
        return students.collect(Collectors.groupingBy(Student::getDepartment, Collectors.counting()));
    }

    public static Map<String, List<String>> getStudentNamesByDepartment(Stream<Student> students) {
        return students.collect(Collectors.groupingBy(Student::getDepartment, Collectors.mapping(Student::getName, Collectors.toList())));
    }

    public static Map<String, Map<Student.Gender, Long>> getTheNumberOfStudentsByGenderForEachDepartment(Stream<Student> students) {
        return students.collect(Collectors.groupingBy(Student::getDepartment, Collectors.groupingBy(Student::getGender, Collectors.counting())));
    }

    public static Map<String, Double> getPercentageOfPassingStudentsForEachDepartment(Stream<Student> students) {
        Collection<Student> studentsAct = students.collect(Collectors.toList());

        Map<String, Long> numberOfStudentsByDepartment = getNumberOfStudentsByDepartment(studentsAct.stream());
        Map<String, Long> numberOfPassingStudentsByDepartment = getNumberOfStudentsByDepartment(studentsAct.stream().filter(s -> s.getGrade() >= Student.PASSING_GRADE));
        return numberOfPassingStudentsByDepartment.entrySet().stream()
                .collect(Collectors.toMap(Map.Entry::getKey, e -> ((double) e.getValue() / numberOfStudentsByDepartment.getOrDefault(e.getKey(), 0L)) * 100.0));
    }

}

class GroupByTests {
    private static Student[] students;

    @BeforeAll
    static void setUp() {
        Student galina = new Student("Galina", 95, "Philology", Student.Gender.FEMALE);
        Student anton = new Student("Anton", 90, "CS", Student.Gender.MALE);
        Student jack = new Student("Jack", 82, "Philology", Student.Gender.MALE);
        Student mike = new Student("Mike", 60, "Philology", Student.Gender.MALE);
        Student jane = new Student("Jane", 65, "CS", Student.Gender.FEMALE);

        students = new Student[]{ galina, anton, jack, mike, jane };
    }

    @Test
    public void basicTestGetAverageGradeByDepartment() {
        Map<String, Double> actual = getAverageGradeByDepartment(Arrays.stream(students));
        Map<String, Double> expected = new HashMap<>();
        expected.put("CS", 77.5);
        expected.put("Philology", 79.0);

        assertEquals(expected, actual);
    }

    @Test
    public void basicTestGetNumberOfStudentsByDepartment() {
        Map<String, Long> actual = getNumberOfStudentsByDepartment(Arrays.stream(students));
        Map<String, Long> expected = new HashMap<>();
        expected.put("CS", 2L);
        expected.put("Philology", 3L);

        assertEquals(expected, actual);
    }

    @Test
    public void basicTestGetStudentNamesByDepartment() {
        Map<String, List<String>> actual = getStudentNamesByDepartment(Arrays.stream(students));
        List<String> list1 = new ArrayList<>(Arrays.asList("Galina", "Jack", "Mike"));
        List<String> list2 = new ArrayList<>(Arrays.asList("Anton", "Jane"));
        Map<String, List<String>> expected = new HashMap<>();
        expected.put("Philology", list1);
        expected.put("CS", list2);

        assertEquals(expected, actual);
    }

    @Test
    public void basicTestGetTheNumberOfStudentsByGenderForEachDepartment() {
        Map<String, Map<Student.Gender, Long>> actual = getTheNumberOfStudentsByGenderForEachDepartment(Arrays.stream(students));
        Map<String, Map<Student.Gender, Long>> expected = new HashMap<>();
        Map<Student.Gender, Long> map1 = new HashMap<>();
        Map<Student.Gender, Long> map2 = new HashMap<>();
        map1.put(Student.Gender.MALE, 1L);
        map1.put(Student.Gender.FEMALE, 1L);
        map2.put(Student.Gender.MALE, 2L);
        map2.put(Student.Gender.FEMALE, 1L);
        expected.put("CS", map1);
        expected.put("Philology", map2);

        assertEquals(expected, actual);
    }

    @Test
    public void basicTestGetTheNumberOfPassingStudentsByDepartment() {
        Map<String, Double> actual = getPercentageOfPassingStudentsForEachDepartment(Arrays.stream(students));
        Map<String, Double> expected = new HashMap<>();
        expected.put("CS", 50.0);
        expected.put("Philology", 2.0 / 3.0 * 100);

        assertEquals(expected, actual);
    }

}

@Data
@AllArgsConstructor
class Student {
    private String name;
    private double grade;
    private String department;
    private Gender gender;

    public static final double PASSING_GRADE = 70.0;

    public enum Gender {
        MALE,
        FEMALE
    }
}
