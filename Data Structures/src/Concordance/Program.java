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

    public static final String DEFAULT_OUTPUT_FILE_PATH = "Data Structures/src/Concordance/output.txt";

    private static String workingFilePath;
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
            System.out.println("2) Create Output File Again");
            System.out.println("3) Print The Results In Console");
            System.out.println("4) Process Another File");
            System.out.println("\n0) Exit Program");
            choice = scanner.nextInt();
            switch (choice) {
                case 0:
                    break;
                case 1:
                    System.out.println("Enter Word To Search:");
                    concordanceProcessor.search(scanner.next());
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
                default:
                    System.out.println("Invalid Input!");
            }
        } catch (Exception exception) {
            System.out.println(exception.toString());
            scanner.nextLine(); //clear buffer
        }
    }

    private static void init(Scanner scanner) {
        boolean fileProcessed = false, gotInput = false;
        while (!fileProcessed) try {
            System.out.println("\nPlease Choose Which File To Process:");
            System.out.println("1) Enter Your Own Text File Path/Name");
            System.out.println("2) Shrek Movie Script");
            System.out.println("3) Harry Potter and the Philosopher's Stone Book");
            System.out.println("4) Bible - King James Edition");
            System.out.println("5) --");
            switch (scanner.nextInt()) {
                case 1:
                    System.out.println("Enter the file Path/Name");
                    workingFilePath = scanner.next();
                    gotInput = true;
                    break;
                case 2:
                    workingFilePath = SHREK_MOVIE_SCRIPT;
                    gotInput = true;
                    break;
                case 3:
                    workingFilePath = HARRY_POTTER_BOOK_1;
                    gotInput = true;
                    break;
                case 4:
                    workingFilePath = BIBLE_KING_JAMES_EDITION;
                    gotInput = true;
                    break;
                case 5:
                    gotInput = true;
                    break;
                default:
                    System.out.println("Invalid Input!");
            }
            if (gotInput) {
                System.out.println("Please Choose Output File:");
                System.out.println("1) Enter Your Own Output File Path/Name");
                System.out.println("2) Save To Default Output File");
                String outputPath;
                switch (scanner.nextInt()) {
                    case 1:
                        System.out.println("Enter the file Path/Name");
                        outputPath = scanner.next();
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
