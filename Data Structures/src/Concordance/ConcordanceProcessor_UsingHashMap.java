package Concordance;

import java.awt.*;
import java.io.*;
import java.nio.file.Files;

public class ConcordanceProcessor_UsingHashMap {
    public static boolean autoOpenOutput = true;
    private final MyHashMap myHashMap;
    private final String outputPath;

    public ConcordanceProcessor_UsingHashMap(File file, String _outputPath) throws IOException {
        long start = System.currentTimeMillis();

        //O(n) when n is the number of lines
        String[] lines = Files.lines(file.toPath()).toArray(String[]::new);

        /*
            Regex and Split operations - O(num of chars in line) per line -> O(num of chars in file) in total
            We check with regex and leave only letters and whitespaces, then split by whitespaces
         */

        for (int i = 0; i < lines.length; i++) {
            lines[i] = lines[i]
                    .replaceAll("-", " ")
                    .replaceAll("[^\\p{Alpha}\\s]", "")
                    .trim()
                    .toLowerCase();
        }

        // O(n) when n is the number of words in the file
        int size = 0;
        for (String line : lines) {
            if (!line.isEmpty())
                for (String word : line.split("[\\s]+")) {
                    if (!word.isEmpty() && checkForOneLetterWords(word)) {
                        size++;
                    }
                }
        }
        myHashMap = new MyHashMap(size);

        // O(n) when n is the number of words in the file
        for (int i = 0; i < lines.length; i++) {
            if (!lines[i].isEmpty())
                for (String word : lines[i].split("[\\s]+")) {
                    if (!word.isEmpty() && checkForOneLetterWords(word)) {
                        myHashMap.insert(word.toLowerCase(), i + 1);
                    }
                }
        }
        System.out.println(
                "File Processed In " + (System.currentTimeMillis() - start) + "ms (" + lines.length + " lines)"
        );

        outputPath = _outputPath;
    }

    private boolean checkForOneLetterWords(String word) {
        return word.length() != 1 || "aioAIO".contains(word);
    }

    //O(n) when n is the number of words in the text file
    public void printToFile() throws IOException {
        printToFile(outputPath);
    }

    public void printToFile(String filePath) throws IOException {
        long start = System.currentTimeMillis();
        File outFile = new File(filePath);
        PrintWriter printWriter = new PrintWriter(outFile);
        printWriter.println(myHashMap);
        printWriter.close();
        System.out.println(
                "Output File Created In " + (System.currentTimeMillis() - start) + "ms, Open It At <" +
                        filePath + "> For The Results"
        );
        if (autoOpenOutput) Desktop.getDesktop().open(outFile);
    }

    /*
        // O(1)
     */
    public void search(String word) {
        long start = System.currentTimeMillis();
        System.out.print(myHashMap.search(word));
        System.out.println("Search Finished In " + (System.currentTimeMillis() - start) + "ms");
    }

    //O(n) when n is the number of words in the text file
    public String toString() {
        return myHashMap.toString();
    }

}
