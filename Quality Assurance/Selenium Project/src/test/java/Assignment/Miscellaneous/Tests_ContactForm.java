package Assignment.Miscellaneous;

import Assignment.ReadExcl;
import Assignment.SeleniumTest;
import org.junit.Test;
import org.junit.internal.TextListener;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.openqa.selenium.*;

public class Tests_ContactForm extends SeleniumTest {

    public static final String MESSAGE_RECEIVED_MESSAGE = "thanks for the message";
    public static final String INVALID_EMAIL_MESSAGE = "invalid email";
    public static final String INVALID_NAME_MESSAGE = "invalid name";
    public static final String OUT_OF_BOUNDS_MESSAGE = "out of bounds";

    private void fillFields(String recipient_email, String recipient_name, String message_text) {
        clickElementSafely(By.cssSelector("#navbarExample > ul > li:nth-child(2) > a"));
        waitForElement(By.id("recipient-email"));

        if (!recipient_email.isEmpty())
            driver.findElement(By.id("recipient-email")).sendKeys(recipient_email);
        if (!recipient_name.isEmpty())
            driver.findElement(By.id("recipient-name")).sendKeys(recipient_name);
        if (!message_text.isEmpty())
            driver.findElement(By.id("message-text")).sendKeys(message_text);

        driver.findElement(By.cssSelector("#exampleModal > div > div > div.modal-footer > button.btn.btn-primary")).click();
    }


    @Test
    public void Test_EmptyFields() {
        initDefaults();

        fillFields("", "", "");

        assertAlertPresent("No alert for empty fields");
        myAssertFalse(driver.switchTo().alert().getText().toLowerCase().contains(MESSAGE_RECEIVED_MESSAGE)
                , "Sent message with empty fields");
    }

    @Test
    public void Test_InvalidEmail() {
        initDefaults();

        fillFields(
                ReadExcl.getStringFromCell(2, 'B'),     // invalid mail
                ReadExcl.getStringFromCell(3, 'B'),     // valid name
                ReadExcl.getStringFromCell(4, 'B')      // valid message
        );

        assertAlertPresent("No alert for invalid email");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(INVALID_EMAIL_MESSAGE)
                , "Missing 'invalid email' message");
    }

    @Test
    public void Test_InvalidName() {
        initDefaults();

        fillFields(
                ReadExcl.getStringFromCell(2, 'C'),     // valid mail
                ReadExcl.getIntegerFromCell(3, 'C'),    // invalid name
                ReadExcl.getStringFromCell(4, 'C')      // valid message
        );

        assertAlertPresent("No alert for invalid name");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(INVALID_NAME_MESSAGE)
                , "Missing 'invalid name' message");
    }

    @Test
    public void Test_OutOfBoundsMessage() {
        initDefaults();

        fillFields(
                ReadExcl.getStringFromCell(2, 'D'),     // valid email
                ReadExcl.getStringFromCell(3, 'D'),     // valid name
                ReadExcl.getStringFromCell(4, 'D')      //invalid message
        );

        assertAlertPresent("No alert for out of bounds message");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(OUT_OF_BOUNDS_MESSAGE)
                , "Missing 'out of bounds message' message");
    }

    @Test
    public void Test_ValidContactForm() {
        initDefaults();

        fillFields(
                ReadExcl.getStringFromCell(2, 'E'),     // valid email
                ReadExcl.getStringFromCell(3, 'E'),     // valid name
                ReadExcl.getStringFromCell(4, 'E')      // valid message
        );

        assertAlertPresent("No alert for successful submission");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(MESSAGE_RECEIVED_MESSAGE)
                , "Missing 'message received' message");
    }

    public static void main(String[] args) {
        JUnitCore junit = new JUnitCore();
        junit.addListener(new TextListener(System.out));
        Result result = junit.run(Tests_ContactForm.class);
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