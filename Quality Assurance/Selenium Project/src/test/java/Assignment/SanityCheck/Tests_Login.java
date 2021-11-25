package Assignment.SanityCheck;

import Assignment.ReadExcl;
import Assignment.SeleniumTest;
import org.junit.Test;
import org.junit.internal.TextListener;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.openqa.selenium.*;

import java.time.LocalDateTime;
import java.util.UUID;

public class Tests_Login extends SeleniumTest {

    public static final String EMPTY_FIELDS_ERROR_MESSAGE = "please fill";
    public static final String NON_EXISTING_USER_ERROR_MESSAGE = "user does not exist";
    public static final String WRONG_PASSWORD_ERROR_MESSAGE = "wrong password";

    public static final String GENERIC_PASSWORD = ReadExcl.getIntegerFromCell(10, 'C');
    public static final String VALID_PASSWORD_USERNAME = ReadExcl.getStringFromCell(12, 'B');
    public static final String VALID_PASSWORD_PASSWORD = ReadExcl.getStringFromCell(12, 'C');
    public static final String INVALID_PASSWORD_USERNAME = ReadExcl.getStringFromCell(11, 'B');
    public static final String INVALID_PASSWORD_PASSWORD = ReadExcl.getStringFromCell(11, 'C');


    private String getUniqueRandomString() {
        LocalDateTime ldt = LocalDateTime.now();
        return UUID.randomUUID().toString()
                + ldt.getYear()
                + ldt.getDayOfYear()
                + ldt.getDayOfWeek()
                + ldt.getHour()
                + ldt.getMinute()
                + ldt.getSecond();
    }

    private void waitAndAcceptAlert() {
        sleep(1500);
        driver.switchTo().alert().accept();
    }

    @Test
    public void Test_EmptyFields() {
        initDefaults();
        login("", "");

        assertAlertPresent("No alert for / Sent Message With: Empty Fields");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(EMPTY_FIELDS_ERROR_MESSAGE),
                "Missing Empty Fields Error Message!");
    }

    @Test
    public void Test_NonExistingUser() {
        initDefaults();

        login(getUniqueRandomString(), GENERIC_PASSWORD);

        assertAlertPresent("No alert for / Logged in as a: non-existing user");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(NON_EXISTING_USER_ERROR_MESSAGE),
                "Missing Non Existing User Error Message!");
    }

    @Test
    public void Test_ValidUserWrongPassword() {
        initDefaults();
        login(INVALID_PASSWORD_USERNAME, INVALID_PASSWORD_PASSWORD);

        assertAlertPresent("No alert for / Logged in with: wrong password");
        myAssertTrue(driver.switchTo().alert().getText().toLowerCase().contains(WRONG_PASSWORD_ERROR_MESSAGE),
                "Missing Wrong Password Error Message!");
    }

    @Test
    public void Test_ValidLoginFirstTry() {
        initDefaults();
        login(VALID_PASSWORD_USERNAME, VALID_PASSWORD_PASSWORD);

        waitForElement(By.id("nava"));
        By logoutBtn = By.id("logout2");
        myAssertTrue(isElementPresent(logoutBtn), "Did not log in / no indication");
    }

    @Test
    public void Test_ValidLoginSecondTry() {
        initDefaults();
        login(INVALID_PASSWORD_USERNAME, INVALID_PASSWORD_PASSWORD);

        waitAndAcceptAlert();

        initDefaults();
        login(VALID_PASSWORD_USERNAME, VALID_PASSWORD_PASSWORD);

        waitForElement(By.id("nava"));
        By logoutBtn = By.id("logout2");
        myAssertTrue(isElementPresent(logoutBtn), "Did not log in / no indication");
    }

    @Test
    public void Test_ValidLoginThirdTry() {
        initDefaults();
        login(INVALID_PASSWORD_USERNAME, INVALID_PASSWORD_PASSWORD);
        waitAndAcceptAlert();
        initDefaults();
        login(INVALID_PASSWORD_USERNAME, INVALID_PASSWORD_PASSWORD);
        waitAndAcceptAlert();
        initDefaults();
        login(VALID_PASSWORD_USERNAME, VALID_PASSWORD_PASSWORD);

        waitForElement(By.id("nava"));
        By logoutBtn = By.id("logout2");
        myAssertTrue(isElementPresent(logoutBtn), "Did not log in / no indication");
    }

    @Test
    public void Test_ValidLoginAfterThreeTries() {
        initDefaults();
        for (int i = 0; i < 3; i++) {
            login(INVALID_PASSWORD_USERNAME, INVALID_PASSWORD_PASSWORD); // 3 wrong logins
            waitAndAcceptAlert();
            initDefaults();
        }
        login(VALID_PASSWORD_USERNAME, VALID_PASSWORD_PASSWORD); //valid login

        assertAlertPresent("No Alert for / Logged in while: supposed blocked after three tries");
    }

    public static void main(String[] args) {
        JUnitCore junit = new JUnitCore();
        junit.addListener(new TextListener(System.out));
        Result result = junit.run(Tests_Login.class);
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