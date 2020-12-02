package Snippets;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class WeightedAvgCalculatorJava {

    public static void main(String[] args) {
        try {
            String filePath = getFilePathFromJFC();
            WeightedAvgCalculatorJava wac = new WeightedAvgCalculatorJava(filePath);
            wac.printAll();
            wac.printAverage();
            wac.printAllRanges();

        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private static JFileChooser jfc;

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

        Files.lines(Path.of(filePath))
                .filter(l -> !l.isEmpty())
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
        System.out.printf("\nAverage - %.3f\n", getAvg());
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
        marks.forEach(t -> System.out.printf("%s - %d (%.1f nz)\n", t.first, t.second, t.third));
    }

}