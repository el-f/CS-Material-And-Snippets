package Concordance;

import java.io.*;
import java.nio.file.Files;

public class ConcordanceProcessor {
    CellsBinarySearchTree tree;
    String outputPath;

    public ConcordanceProcessor(File file, String _outputPath) throws IOException {

        tree = new CellsBinarySearchTree();

        String[] lines = Files.lines(file.toPath()).toArray(String[]::new);

        //O(n * m) when n is the number of lines and m is the number of characters in each line
        for (int i = 0; i < lines.length; i++) {
            lines[i] = lines[i].toLowerCase().replaceAll("[^a-zA-Z\\s+]", "").trim();
        }

        /*
            Average Case: O(n * [(m * lg(m*n) + c])
            Worst Case: O([n*m]^2 + c)
            when n is the number of lines
            m is the number of words in each line
            c is the number of characters in each line
         */
        for (int i = 0; i < lines.length; i++) {
            if (!lines[i].isEmpty())
                for (String word : lines[i].split("[\\s]+")) { //Split operation - O(num of chars in line)
                    if (!word.isEmpty()) {
                        tree.insert(new Cell(word, i + 1)); //lg(n*m)
                    }
                }
        }
        System.out.println("~Processed " + lines.length + " Lines~");

        outputPath = _outputPath;
        printToFile();
    }

    //O(n * m) when n is the number of words and m is the number of lines the word appears in
    public String toString() {
        return tree.toString();
    }

    //O(n * m) ~ O(n) when n is the number of words and m is number of lines the word appears in
    public void printToFile() throws FileNotFoundException {
        File outFile = new File(outputPath);
        PrintWriter printWriter = new PrintWriter(outFile);
        printWriter.println(tree);
        printWriter.close();
    }

    /*
        Average Case: O(lgn * m)
        Worst Case: O(n + m) - (in case in which the words in the file are sorted)
        when n is the number of words in the tree and m is the number of lines the found word appears in
     */
    public void search(String word) {
        System.out.println(tree.search(word));
    }

    static class Cell {
        String word;
        MyLinkedList lineNumbers;

        Cell(String _word, int lineNumber) {
            word = _word;

            //O(1)
            lineNumbers = new MyLinkedList(lineNumber);
        }

        //O(1)
        void insert(int lineNumber) {
            lineNumbers.insert(lineNumber);
        }

        //O(n) when n is the size of the lineNumbers List
        @Override
        public String toString() {
            return String.format(
                    "%s -> %s\n",
                    word,
                    lineNumbers
            );
        }
    }

}
