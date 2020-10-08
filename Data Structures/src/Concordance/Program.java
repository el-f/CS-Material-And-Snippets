package Concordance;

import java.io.File;
import java.rmi.UnexpectedException;
import java.util.Scanner;

public class Program {
    public static final String SHREK_MOVIE_SCRIPT =
            "Data Structures/src/Concordance/DefaultInputFiles/shrekMovieScript.txt";

    public static final String HARRY_POTTER_BOOK_1 =
            "Data Structures/src/Concordance/DefaultInputFiles/Harry Potter and the Philosopher's Stone.txt";

    public static final String BIBLE_KING_JAMES_EDITION =
            "Data Structures/src/Concordance/DefaultInputFiles/BibleKingJamesEdition.txt";

    public static final String LORD_OF_THE_RINGS = "Data Structures/src/Concordance/DefaultInputFiles/lotr.txt";

    public static final String DEFAULT_OUTPUT_FILE_PATH = "Data Structures/src/Concordance/output.txt";

    private static ConcordanceProcessor concordanceProcessor;

    public static void main(String[] args) {
        showMenu();
    }

    private static void showMenu() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Welcome To My Concordance Program!");
        init(scanner);
        int choice = -1;
        while (choice != 0) try {
            System.out.println("> Choose:");
            System.out.println("1) Search For A Specific Word");
            System.out.println("2) Recreate Output File");
            System.out.println("3) Print The Results In Console (may not print all for very large outputs)");
            System.out.println("4) Process Another File");
            System.out.println("5) Choose How The Output Looks");
            System.out.println("\n0) Exit Program");
            choice = scanner.nextInt();
            switch (choice) {
                case 0:
                    break;
                case 1:
                    System.out.println("Enter The Word To Search For:");
                    concordanceProcessor.search(scanner.next().toLowerCase());
                    break;
                case 2:
                    concordanceProcessor.printToFile();
                    break;
                case 3:
                    System.out.println(concordanceProcessor);
                    break;
                case 4:
                    init(scanner);
                    break;
                case 5:
                    System.out.println("1) Print All Line Numbers In One Line After Each Word");
                    System.out.println("2) Print The Line Numbers With Line Breaks And Indentation");
                    switch (scanner.nextInt()) {
                        case 1:
                            MyLinkedList.breakOutputLine = false;
                            break;
                        case 2:
                            MyLinkedList.breakOutputLine = true;
                            break;
                        default:
                            System.out.println("Invalid Input!");
                    }
                    break;
                default:
                    System.out.println("Invalid Input!");
            }
        } catch (Exception exception) {
            System.out.println(exception.toString());
            scanner.nextLine(); //clear buffer
        }
    }

    private static void init(Scanner scanner) {
        boolean fileProcessed = false;
        while (!fileProcessed) try {
            System.out.println("\nPlease Choose Which File To Process:");
            System.out.println("1) Enter Your Own Text File Path/Name");
            System.out.println("2) Shrek Movie Script (1653 lines)");
            System.out.println("3) Harry Potter and the Philosopher's Stone Book (6065 lines)");
            System.out.println("4) The Lord of the Rings Books (48722 lines)");
            System.out.println("5) Bible - King James Edition (99809 lines)");
            String workingFilePath = null;
            switch (scanner.nextInt()) {
                case 1:
                    System.out.println("Enter the file Path/Name");
                    scanner.nextLine(); //clear buffer
                    workingFilePath = scanner.nextLine();
                    break;
                case 2:
                    workingFilePath = SHREK_MOVIE_SCRIPT;
                    break;
                case 3:
                    workingFilePath = HARRY_POTTER_BOOK_1;
                    break;
                case 4:
                    workingFilePath = LORD_OF_THE_RINGS;
                    break;
                case 5:
                    workingFilePath = BIBLE_KING_JAMES_EDITION;
                    break;
                default:
                    System.out.println("Invalid Input!");
            }
            if (workingFilePath != null) {
                System.out.println("Please Choose Output File:");
                System.out.println("1) Enter Your Own Output File Path/Name");
                System.out.println("2) Save To Default Output File");
                String outputPath;
                switch (scanner.nextInt()) {
                    case 1:
                        System.out.println("Enter the file Path/Name");
                        scanner.nextLine(); //clear buffer
                        outputPath = scanner.nextLine();
                        break;
                    case 2:
                        outputPath = DEFAULT_OUTPUT_FILE_PATH;
                        break;
                    default:
                        throw new UnexpectedException("Invalid Input!");
                }
                long start = System.currentTimeMillis();
                concordanceProcessor = new ConcordanceProcessor(new File(workingFilePath), outputPath);

                fileProcessed = true;
                System.out.printf(
                        "File Successfully Processed In %dms!\nCheck Output File (%s) For The Results Or Print Them Here\n",
                        System.currentTimeMillis() - start,
                        outputPath
                );
            }
        } catch (Exception exception) {
            System.out.println(exception.toString());
            scanner.nextLine(); //clear buffer
        }
    }
}
