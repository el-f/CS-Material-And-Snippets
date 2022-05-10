package Assignment;

import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Rule;
import org.junit.rules.TestWatcher;
import org.junit.runner.Description;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.io.IOException;
import java.nio.file.Paths;
import java.time.Duration;
import java.util.HashMap;
import java.util.Map;

import static Assignment.MyLogger.LogLevel.*;

public abstract class SeleniumTest {
    protected WebDriver driver;
    protected Map<String, Object> vars;
    protected JavascriptExecutor js;
    protected WebDriverWait driverWait;

    protected MyLogger logger;

    public static final String ELAZAR_DRIVER = "C:/chromedriver_win32/chromedriver.exe";
    //    public static final String GAL_DRIVER = "C:/Users/galka/Desktop/לימודים/שנה ב/QA/chromedriver.exe";
    public static final int IMPLICIT_WAIT_TIME_MS = 1100;

    @Rule(order = Integer.MIN_VALUE)
    public TestWatcher watchman = new TestWatcher() {


        @Override
        protected void starting(Description description) {
            // In our opinion in our use case this is redundant and just bloating the logfile
//            logger.log(INFO, "Starting... " + description.getMethodName());
        }

        @Override
        protected void failed(Throwable e, Description description) {
            logger.log(DEBUG, "FAILED - " + description.getMethodName() + " | Reason: " + e.getMessage());
        }

        @Override
        protected void succeeded(Description description) {
            logger.log(INFO, "PASSED - " + description.getMethodName());
        }
    };

    protected void getSite() {
        driver.get("https://www.demoblaze.com/");
    }

    protected void setDefaultSize() {
        driver.manage().window().setSize(new Dimension(1280, 720));
    }

    protected void initDefaults() {
        getSite();
        setDefaultSize();
    }

    protected void waitForElement(By locator) {
        sleep(IMPLICIT_WAIT_TIME_MS); // just to be sure
        driverWait.until(ExpectedConditions.visibilityOfElementLocated(locator));
    }

    protected void clickElementSafely(By locator) {
        waitForElement(locator); // just to be sure
        driverWait.until(ExpectedConditions.elementToBeClickable(locator));
        driver.findElement(locator).click();
    }

    protected void sleep(int ms) {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            logger.log(FATAL, e.toString());
            e.printStackTrace();
            System.exit(1);
        }
    }

    protected boolean isAlertPresent() {
        try {
            sleep(IMPLICIT_WAIT_TIME_MS); // give time for alert to pop
            driver.switchTo().alert();
            return true;
        } catch (NoAlertPresentException Ex) {
            return false;
        }
    }

    protected void assertAlertPresent(String failMessage) {
        myAssertTrue(isAlertPresent(), failMessage + " (Expected Alert Not Present)");
    }

    protected boolean isElementPresent(By element) {
        return driver.findElements(element).size() > 0;
    }

    protected void myAssertTrue(boolean condition, String failMessage) {
        if (!condition) {
            throw new AssertionError(failMessage);
        }
    }

    protected void myAssertFalse(boolean condition, String failMessage) {
        if (condition) {
            throw new AssertionError(failMessage);
        }
    }

    protected void myAssertEquals(Object o1, Object o2, String failMessage) {
        if (!o1.equals(o2)) {
            throw new AssertionError(failMessage);
        }
    }

    protected void login(String username, String password) {
        driver.findElement(By.id("login2")).click();

        By loginField = By.id("loginusername");
        waitForElement(loginField);

        if (!username.isEmpty()) {
            driver.findElement(loginField).sendKeys(username);
        }
        if (!password.isEmpty()) {
            driver.findElement(By.id("loginpassword")).sendKeys(password);
        }

        clickElementSafely(By.cssSelector("button[onclick='logIn()']")); // click login button
    }

    @BeforeClass
    public static void loadDefaultExcel() {
        try {
            ReadExcl.readExcel(Paths.get("").toAbsolutePath() + "/src/test/java/Assignment", "DATA.xls", "sheet1");
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("Failed loading the Excel file, please verify its location");
            System.exit(1);
        }
    }

    @Before
    public void setUp() {
        System.setProperty("webdriver.chrome.driver", ELAZAR_DRIVER);
        driver = new ChromeDriver();
        js = (JavascriptExecutor) driver;
        vars = new HashMap<>();
        driverWait = new WebDriverWait(driver,
                                       Duration.ofSeconds(5));

        logger = new MyLogger(
                "logs/" + this.getClass().getPackage().getName() + ".log",
                this.getClass().getSimpleName()
        );
    }

    @After
    public void tearDown() {
//        sleep(5000);
        driver.quit();
    }
}
