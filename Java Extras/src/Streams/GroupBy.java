package Streams;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.*;
import java.util.stream.*;

import org.junit.jupiter.api.BeforeEach;
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

}

class GroupByTests {
    private Student[] students;
    private Student[] randomStudents;

    @BeforeEach
    public void setUp() {
        //Generate a basic array of students:
        Student galina = new Student("Galina", 95, "Philology", Student.Gender.FEMALE);
        Student anton = new Student("Anton", 90, "CS", Student.Gender.MALE);
        Student jack = new Student("Jack", 82, "Philology", Student.Gender.MALE);
        Student mike = new Student("Mike", 60, "Philology", Student.Gender.MALE);
        Student jane = new Student("Jane", 65, "CS", Student.Gender.FEMALE);

        students = new Student[]{ galina, anton, jack, mike, jane };

        //Generate a random array of students:
        Student.Gender[] genders = Student.Gender.values();

        int randomLength = (int) (Math.random() * 100 + 1);
        randomStudents = new Student[randomLength];

        for (int i = 0; i < randomStudents.length; i++) {

            int randomNameNum = (int) (Math.random() * 1000);
            int randomDepartmentNum = (int) (Math.random() * 10);
            int randomGenderIndex = (int) (Math.random() * 2);

            String name = "Student" + randomNameNum;
            double grade = Math.random() * (100 - 40) + 40;
            String department = "Department" + randomDepartmentNum;
            Student.Gender gender = genders[randomGenderIndex];

            randomStudents[i] = new Student(name, grade, department, gender);

        }
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
    public void randomTestGetAverageGradeByDepartment() {
        Map<String, Double> expected = Stream.of(randomStudents)
                .collect(Collectors.groupingBy(Student::getDepartment,
                                               Collectors.averagingDouble(Student::getGrade)));


        Map<String, Double> actual = getAverageGradeByDepartment(Arrays.stream(randomStudents));

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
    public void randomTestGetNumberOfStudentsByDepartment() {
        Map<String, Long> expected = Arrays.stream(randomStudents)
                .collect(Collectors.groupingBy((Student::getDepartment),
                                               Collectors.counting()));

        Map<String, Long> actual = getNumberOfStudentsByDepartment(Arrays.stream(randomStudents));

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
    public void randomTestGetStudentNamesByDepartment() {
        Map<String, List<String>> expected = Arrays.stream(randomStudents)
                .collect(Collectors.groupingBy(Student::getDepartment,
                                               Collectors.mapping(Student::getName,
                                                                  Collectors.toList())));

        Map<String, List<String>> actual = getStudentNamesByDepartment(Arrays.stream(randomStudents));

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
    public void randomTestGetTheNumberOfStudentsByGenderForEachDepartment() {
        Map<String, Map<Student.Gender, Long>> actual = getTheNumberOfStudentsByGenderForEachDepartment(Arrays.stream(randomStudents));
        Map<String, Map<Student.Gender, Long>> expected = Arrays.stream(randomStudents)
                .collect(Collectors.groupingBy(Student::getDepartment,
                                               Collectors.groupingBy(Student::getGender, Collectors.counting())));

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
