package Snippets;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class WeightedAvgCalculatorJava {

    public static final boolean GUI = true;

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        try {
            System.out.println("--- Weighted Avg Calculator By Elazar Fine ---");
            System.out.println("Please make sure your file is in the supported format!\n");
            String filePath;
            if (GUI) filePath = getFilePathFromJFC();
            else {
                System.out.println("Pleaser enter the file's path or just name if it's in the same directory");
                filePath = scanner.nextLine();
            }
            WeightedAvgCalculatorJava wac = new WeightedAvgCalculatorJava(filePath);
            wac.printAll();
            wac.printAverage();
            wac.printRoundedAverage();
            System.out.println();
            wac.printAllRanges();

            System.out.println("\nPress Enter to exit");
            scanner.nextLine();
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }


    private static final JFileChooser jfc;

    static {
        jfc = new JFileChooser(Paths.get("").toAbsolutePath() + "/");
        jfc.setFileFilter(new FileNameExtensionFilter("*.txt", "txt"));
    }

    private static class Triple<F, S, T> {
        F first;
        S second;
        T third;

        Triple(F first, S second, T third) {
            this.first = first;
            this.second = second;
            this.third = third;
        }

    }

    private final List<Triple<String, Integer, Double>> marks;

    private final Double allNaz;

    public static String getFilePathFromJFC() throws Exception {
        if (jfc.showOpenDialog(null) == JFileChooser.CANCEL_OPTION) {
            throw new Exception("Canceled");
        }
        return jfc.getSelectedFile().getAbsolutePath();
    }

    public WeightedAvgCalculatorJava(String filePath) throws IOException {
        marks = new ArrayList<>();

        Files.lines(new File(filePath).toPath())
                .filter(l -> !l.isEmpty() && !l.startsWith("#"))
                .map(l -> l.split(","))
                .forEach(l -> marks.add(
                                 new Triple<>(l[0].trim(),
                                              Integer.parseInt(l[1].trim()),
                                              Double.parseDouble(l[2].trim()))
                         )
                );

        allNaz = marks.stream().map(t -> t.third).mapToDouble(Double::doubleValue).sum();
    }

    public double getAvg() {
        return marks.stream().map(t -> t.second * t.third / allNaz).mapToDouble(Double::doubleValue).sum();
    }

    public void printAverage() {
        System.out.printf(">>> Average: %.3f\n", getAvg());
    }

    public void printRoundedAverage() {
        System.out.printf(">>> Rounded Average: %d\n", Math.round(getAvg()));
    }

    public void printRange(int low, int high) {
        System.out.printf(
                "%d Marks at Range of (%d-%d) Out of %d Marks\n",
                (int) marks.stream().filter(t -> inRange(t.second, low, high)).count(),
                low, high,
                marks.size()
        );
    }

    private boolean inRange(int x, int low, int high) {
        return low <= x && x <= high;
    }

    public void printAllRanges() {
        for (int i = 0; i <= 90; i += 10) {
            int I = i;
            if (marks.stream().anyMatch(t -> inRange(t.second, I, I + 9))) {
                printRange(i, i + 9);
            }
        }
        printRange(100, 100);
    }

    public void printAll() {
        TableList tl = new TableList("Course", "%", "NZ").withUnicode(true);
        marks.forEach(t -> tl.addRow(t.first, t.second, t.third));
        tl.print();
    }

}