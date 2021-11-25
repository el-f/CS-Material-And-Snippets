package Assignment.SanityCheck;

import Assignment.ReadExcl;
import Assignment.SeleniumTest;
import org.junit.Test;
import org.junit.internal.TextListener;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.openqa.selenium.By;

public class Tests_AddProduct extends SeleniumTest {

    public static final String PRODUCT_ADDED_MESSAGE = "added";

    @Test
    public void Test_AddProductThatDoesntExist() {
        setDefaultSize();

        //unique invalid product page
        driver.get(ReadExcl.getStringFromCell(2, 'A'));

        // click add product
        clickElementSafely(By.xpath("/html/body/div[5]/div/div[2]/div[2]/div/a"));

        assertAlertPresent("Added / No alert for: Invalid Product!");
        myAssertFalse(driver.switchTo().alert().getText().toLowerCase().contains(PRODUCT_ADDED_MESSAGE),
                "Received Product Added Message!");
    }

    @Test
    public void Test_AddProduct() {
        initDefaults();

        // click valid product
        clickElementSafely(By.cssSelector("#tbodyid > div:nth-child(1) > div > a > img"));

        // click add product
        clickElementSafely(By.xpath("//*[@id=\"tbodyid\"]/div[2]/div/a"));

        assertAlertPresent("Did not add product / no indication");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(PRODUCT_ADDED_MESSAGE),
                "Missing Product Added Message");
    }

    public static void main(String[] args) {
        JUnitCore junit = new JUnitCore();
        junit.addListener(new TextListener(System.out));
        Result result = junit.run(Tests_AddProduct.class);
        if (result.getFailureCount() > 0) {
            result.getFailures().forEach(System.out::println);
            System.out.println("Test failed.");
            System.exit(1);
        } else {
            System.out.println("Test finished successfully.");
            System.exit(0);
        }
    }
}