package Assignment;

import Assignment.Miscellaneous.Tests_ContactForm;
import Assignment.SanityCheck.*;
import Assignment.Users.*;
import org.junit.internal.TextListener;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;


public class Assignment {

    public static int totalTests = 0;
    public static int totalFails = 0;
    public static HashMap<String, Boolean> batchesResults = new HashMap<>();
    public static HashMap<String, List<String>> failuresDetails = new HashMap<>();

    public static void main(String[] args) {
        long start = System.currentTimeMillis();

        runTestsBatch(
                "Sanity Check",
                Tests_Login.class,
                Tests_AddProduct.class,
                Tests_CartPage.class,
                Tests_PurchaseForm.class
        );

        runTestsBatch(
                "Users",
                Tests_Registration.class,
                Tests_Logout.class,
                Tests_UserSpecificElements.class
        );

        runTestsBatch(
                "Miscellaneous",
                Tests_ContactForm.class
        );

        long end = System.currentTimeMillis();
        System.out.println("\n~~~~~~~~~~~~~~~~~~~~\n");
        System.out.println("Failures Summary:");
        failuresDetails.forEach((batch_name, failures) -> {
            System.out.println(batch_name + " Failures:");
            failures.forEach(System.out::println);
            System.out.println();
        });

        System.out.println("~~~~~~~~~~~~~~~~~~~~\n");
        System.out.println("Summary:");
        batchesResults.forEach(
                (batch_name, passed) -> System.out.println(batch_name + (passed ? " PASSED" : " FAILED"))
        );
        System.out.println("\nTotal Tests (All batches): " + totalTests);
        System.out.println("Total Fails (All batches): " + totalFails);
        System.out.printf("Total Runtime: %.2f minutes\n", (end - start) / 1000 / 60.0);
        if (totalFails == 0)
            System.exit(0);
        System.exit(1);
    }

    private static void runTestsBatch(String batchName, Class<?>... testClasses) {
        JUnitCore junit = new JUnitCore();
        junit.addListener(new TextListener(System.out));

        Result result = junit.run(testClasses);

        totalTests += result.getRunCount();

        boolean passed = result.getFailureCount() == 0;
        batchesResults.put(batchName, passed);

        if (!passed) {
            failuresDetails.put(batchName, new ArrayList<>());
            totalFails += result.getFailureCount();
            result.getFailures().forEach(failure -> failuresDetails.get(batchName).add(failure.toString()));
            System.out.println(batchName + " batch failed.");
        } else {
            System.out.println("All " + batchName + " Tests finished successfully.");
        }
    }


}