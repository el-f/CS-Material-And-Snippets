package Assignment.Users;

import Assignment.ReadExcl;
import Assignment.SeleniumTest;
import org.junit.Test;
import org.junit.internal.TextListener;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.openqa.selenium.By;

public class Tests_UserSpecificElements extends SeleniumTest {

    public static final String USERNAME = ReadExcl.getStringFromCell(11, 'B');
    public static final String PASSWORD = ReadExcl.getStringFromCell(12, 'B');


    @Test
    public void Test_LoginMemberInterface() {
        initDefaults();

        login(USERNAME, PASSWORD);

        waitForElement(By.id("nava")); // wait for page load

        sleep(1000);

        myAssertFalse(driver.findElement(By.id("login2")).isDisplayed(), "Login is displayed");
        myAssertFalse(driver.findElement(By.id("signin2")).isDisplayed(), "Sign up is displayed");

        myAssertTrue(driver.findElement(By.id("logout2")).isDisplayed(), "Logout isn't displayed");
        myAssertTrue(driver.findElement(By.id("nameofuser")).isDisplayed(), "Welcome isn't displayed");
    }

    @Test
    public void Test_LogoutMemberInterface() {
        initDefaults();

        login(USERNAME, PASSWORD);

        clickElementSafely(By.id("logout2")); // log out

        myAssertTrue(driver.findElement(By.id("login2")).isDisplayed(), "Login isn't displayed");
        myAssertTrue(driver.findElement(By.id("signin2")).isDisplayed(), "Sign up isn't displayed");

        myAssertFalse(driver.findElement(By.id("logout2")).isDisplayed(), "Logout is displayed");
        myAssertFalse(driver.findElement(By.id("nameofuser")).isDisplayed(), "Welcome is displayed");
    }

    public static void main(String[] args) {
        JUnitCore junit = new JUnitCore();
        junit.addListener(new TextListener(System.out));
        Result result = junit.run(Tests_UserSpecificElements.class);
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