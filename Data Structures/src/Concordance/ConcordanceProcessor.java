package Concordance;

import java.io.*;
import java.nio.file.Files;

public class ConcordanceProcessor {
    private final MyBinarySearchTree tree;
    private final String outputPath;

    public ConcordanceProcessor(File file, String _outputPath) throws IOException {
        long start = System.currentTimeMillis();

        tree = new MyBinarySearchTree();

        //O(n) when n is the number of lines
        String[] lines = Files.lines(file.toPath()).toArray(String[]::new);

        /*
            Average Case -> O(n * [(m * lg(m*n) + c])
            Worst Case -> O([n*m]^2 + c) - (in case in which the words in the file are sorted/reverse sorted)

            > n - number of lines
            > m - number of words in each line
            > c - number of characters in each line

            Or More Simply:

        	Average Case -> O(nlgn + c)
        	Worst Case -> O(n^2 + c) - (in case in which the words in the file are sorted/reverse sorted)

        	> n - total number of words in the file
        	> c - total number of characters in the file

         */
        for (int i = 0; i < lines.length; i++) {
            if (!lines[i].isEmpty())
                /*
                    Regex and Split operations - O(num of chars in line) per line -> O(num of chars in file) in total
                    We check with regex and leave only letters and whitespaces, then split by whitespaces
                 */
                for (String word : lines[i].replaceAll("[^a-zA-Z\\s+]", "").trim().split("[\\s]+")) {
                    if (!word.isEmpty() && checkForOneLetterWords(word)) {
                        tree.insert(word.toLowerCase(), i + 1);
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
    public void printToFile() throws FileNotFoundException {
        printToFile(outputPath);
    }

    public void printToFile(String filePath) throws FileNotFoundException {
        long start = System.currentTimeMillis();
        File outFile = new File(filePath);
        PrintWriter printWriter = new PrintWriter(outFile);
        printWriter.println(tree);
        printWriter.close();
        System.out.println(
                "Output File Created In " + (System.currentTimeMillis() - start) + "ms, Open It At <" +
                        filePath + "> For The Results"
        );
    }

    /*
        Average Case: O(lgn + l)
        Worst Case: O(n + l) - (in case in which the words in the file are sorted)
        when n is the number of words in the tree and l is the number of lines the found word appears in
     */
    public void search(String word) {
        long start = System.currentTimeMillis();
        System.out.print(tree.search(word));
        System.out.println("Search Finished In " + (System.currentTimeMillis() - start) + "ms");
    }

    //O(n) when n is the number of words in the text file
    public String toString() {
        return tree.toString();
    }

}
