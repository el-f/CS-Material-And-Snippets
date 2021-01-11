package Concordance

import java.io.File
import java.nio.file.Paths
import java.util.*

/*
*
* Same as Program_Light.java, but using HashMap instead of Binary Search Tree
*
*/
//-------------------- Change This If Needed --------------------//

val PROJECT_DIR = Paths.get("").toAbsolutePath().toString() + "/Data Structures/src/Concordance/"

//---------------------------------------------------------------//
val SHREK_MOVIE_SCRIPT = PROJECT_DIR + "DefaultInputFiles/shrekMovieScript.txt"
val HARRY_POTTER_BOOK_1 = PROJECT_DIR + "DefaultInputFiles/Harry Potter and the Philosopher's Stone.txt"
val LORD_OF_THE_RINGS = PROJECT_DIR + "DefaultInputFiles/lotr.txt"
val BIBLE_KING_JAMES_EDITION = PROJECT_DIR + "DefaultInputFiles/BibleKingJamesEdition.txt"
val DEFAULT_OUTPUT_FILE_PATH = PROJECT_DIR + "output.txt"
private var concordanceProcessor: BONUS_ConcordanceProcessor_UsingHashMap? = null

fun main() = showMenu()


private fun showMenu() {
    val scanner = Scanner(System.`in`)
    println("Welcome To My Concordance Program!")
    init(scanner)
    var choice = -1
    while (choice != 0) try {
        println("\n> Choose:")
        println("1) Search For A Specific Word")
        println("2) Create An Output File Again")
        println("3) Print The Results In Console (may not print all for very large outputs)")
        println("4) Process Another File")
        println("5) Change How The Output Looks")
        println("6) Toggle Automatic Output File Opening")
        println("7) Get Most Common Word")
        println("\n0) Exit Program")
        choice = scanner.nextInt()
        when (choice) {
            0 -> {
            }
            1 -> {
                println("Enter The Word To Search For:")
                concordanceProcessor!!.search(scanner.next().toLowerCase())
            }
            2 -> {
                println("1) Save To Originally Chosen File")
                println("2) Create A Different File")
                when (scanner.nextInt()) {
                    1 -> concordanceProcessor!!.printToFile()
                    2 -> concordanceProcessor!!.printToFile(chooseOutputPath(scanner))
                    else -> throw Exception("Invalid Input!")
                }
            }
            3 -> print(concordanceProcessor)
            4 -> init(scanner)
            5 -> {
                println("1) Print All Line Numbers In One Line After Each Word")
                println("2) Print The Line Numbers With Line Breaks And Indentation")
                when (scanner.nextInt()) {
                    1 -> MyLinkedList.breakOutputLine = false
                    2 -> MyLinkedList.breakOutputLine = true
                    else -> println("Invalid Input!")
                }
            }
            6 -> {
                println("1) Automatically Open The Outfile")
                println("2) Don't Automatically Open The Outfile")
                when (scanner.nextInt()) {
                    1 -> ConcordanceProcessor.autoOpenOutput = true
                    2 -> ConcordanceProcessor.autoOpenOutput = false
                    else -> println("Invalid Input!")
                }
            }
            7 -> concordanceProcessor!!.printMostCommonWord()
            else -> println("Invalid Input!")
        }
    } catch (exception: Exception) {
        println(exception.toString())
        scanner.nextLine() //clear buffer
    }
}

private fun init(scanner: Scanner) {
    var fileProcessed = false
    while (!fileProcessed) try {
        println("\nPlease Choose Which File To Process:")
        println("1) Enter Your Own Text File Path/Name")
        println("2) Shrek Movie Script (1,653 lines)")
        println("3) Harry Potter and the Philosopher's Stone Book (6,065 lines)")
        println("4) The Lord of the Rings Books (48,722 lines)")
        println("5) Bible - King James Edition (100,182 lines)")
        var workingFilePath: String? = null
        when (scanner.nextInt()) {
            1 -> {
                println("Enter the file Path/Name")
                scanner.nextLine() //clear buffer
                workingFilePath = scanner.nextLine()
            }
            2 -> workingFilePath = SHREK_MOVIE_SCRIPT
            3 -> workingFilePath = HARRY_POTTER_BOOK_1
            4 -> workingFilePath = LORD_OF_THE_RINGS
            5 -> workingFilePath = BIBLE_KING_JAMES_EDITION
            else -> println("Invalid Input!")
        }
        if (workingFilePath != null) {
            concordanceProcessor =
                BONUS_ConcordanceProcessor_UsingHashMap(File(workingFilePath), chooseOutputPath(scanner))
            fileProcessed = true
            concordanceProcessor!!.printToFile()
        }
    } catch (exception: Exception) {
        println(exception.toString())
        scanner.nextLine() //clear buffer
    }
}

@Throws(Exception::class)
private fun chooseOutputPath(scanner: Scanner): String {
    println("Please Choose Output File:")
    println("1) Enter Your Own Output File Path/Name")
    println("2) Save To Default Output File")
    return when (scanner.nextInt()) {
        1 -> {
            println("Enter the file Path/Name")
            scanner.nextLine() //clear buffer
            scanner.nextLine()
        }
        2 -> DEFAULT_OUTPUT_FILE_PATH
        else -> throw Exception("Invalid Input!")
    }
}
