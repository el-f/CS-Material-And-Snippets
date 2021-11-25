package Assignment.Users;


import Assignment.ReadExcl;
import Assignment.SeleniumTest;
import org.junit.Test;
import org.junit.internal.TextListener;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.openqa.selenium.By;

import java.util.UUID;

public class Tests_Registration extends SeleniumTest {

    public static final String EMPTY_FIELDS_MESSAGE = "please fill";
    public static final String EXIST_USER_MESSAGE = "user already exist";
    public static final String USER_SIGN_MESSAGE = "sign up successful";
    public static final String INVALID_USERNAME_MESSAGE = "illegal username";
    public static final String PASSWORD_OUT_OF_BOUNDS_MESSAGE = "out of bounds";

    private void fillFields(String username, String password) {
        clickElementSafely(By.id("signin2"));
        sleep(2000);
        if (!username.isEmpty()) {
            driver.findElement(By.id("sign-username")).sendKeys(username);
        }
        if (!password.isEmpty()) {
            driver.findElement(By.id("sign-password")).sendKeys(password);
        }
        By signUpButton = By.cssSelector("#signInModal > div > div > div.modal-footer > button.btn.btn-primary");
        clickElementSafely(signUpButton);

    }

    @Test
    public void Test_EmptyField() {
        initDefaults();

        fillFields("", "");

        assertAlertPresent("No alert for empty field");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(EMPTY_FIELDS_MESSAGE)
                , "Missing empty fields message");
    }

    @Test
    public void Test_EnterTakenUserName() {
        initDefaults();

        fillFields(
                ReadExcl.getStringFromCell(11, 'B'),
                ReadExcl.getStringFromCell(12, 'B')
        );

        assertAlertPresent("No alert for taken username");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(EXIST_USER_MESSAGE),
                "missing exist user message");
    }

    @Test
    public void Test_RegisterUsernameWithoutLetters() {
        initDefaults();

        fillFields(
                ReadExcl.getIntegerFromCell(2, 'F'), //only numbers
                ReadExcl.getIntegerFromCell(3, 'F')
        );

        sleep(2000);
        assertAlertPresent("No alert for non-alphabetic username");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(INVALID_USERNAME_MESSAGE)
                , "Missing invalid username message");

    }

    @Test
    public void Test_EnterValidInfo() {
        initDefaults();

        fillFields(
                UUID.randomUUID().toString(),
                ReadExcl.getIntegerFromCell(10, 'C')
        );

        sleep(2000);

        assertAlertPresent("No alert for successful registration");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(USER_SIGN_MESSAGE)
                , "Missing user sign message");
    }

    @Test
    public void Test_PasswordOutOfBounds() {
        initDefaults();
        fillFields(
                UUID.randomUUID().toString(),
                UUID.randomUUID().toString() + UUID.randomUUID().toString()
        );
        sleep(2000);
        assertAlertPresent("No alert for out of bounds password");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(PASSWORD_OUT_OF_BOUNDS_MESSAGE)
                , "Missing password out of bounds message");
    }

    public static void main(String[] args) {
        JUnitCore junit = new JUnitCore();
        junit.addListener(new TextListener(System.out));
        Result result = junit.run(Tests_Registration.class);
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