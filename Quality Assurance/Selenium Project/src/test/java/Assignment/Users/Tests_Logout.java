package Assignment.Users;

import Assignment.ReadExcl;
import Assignment.SeleniumTest;
import org.junit.Test;
import org.junit.internal.TextListener;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.openqa.selenium.By;

public class Tests_Logout extends SeleniumTest {

    @Test
    public void Test_LogoutMember() {
        initDefaults();

        String username = ReadExcl.getStringFromCell(11, 'B');
        String password = ReadExcl.getStringFromCell(12, 'B');

        login(username, password);

        clickElementSafely(By.id("logout2"));
        myAssertTrue(driver.findElement(By.id("login2")).isDisplayed(), "Login isn't displayed");
        myAssertTrue(driver.findElement(By.id("signin2")).isDisplayed(), "Sign up isn't displayed");

        myAssertFalse(driver.findElement(By.id("logout2")).isDisplayed(), "Logout is displayed");
        myAssertFalse(driver.findElement(By.id("nameofuser")).isDisplayed(), "Welcome is displayed");
    }

    public static void main(String[] args) {
        JUnitCore junit = new JUnitCore();
        junit.addListener(new TextListener(System.out));
        Result result = junit.run(Tests_Logout.class);
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