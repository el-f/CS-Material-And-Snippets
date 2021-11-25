package Assignment.SanityCheck;

import Assignment.ReadExcl;
import Assignment.SeleniumTest;
import org.junit.Test;
import org.junit.internal.TextListener;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.openqa.selenium.By;

import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.UUID;
import java.util.concurrent.ThreadLocalRandom;

public class Tests_PurchaseForm extends SeleniumTest {

    public static final String EMPTY_FIELDS_ERROR_MESSAGE = "please fill";
    public static final String WRONG_LANGUAGE_ERROR_MESSAGE = "please only use english";
    public static final String CREDIT_CARD_LENGTH_ERROR_MESSAGE = "15-16 digits";
    public static final String NON_INTEGERS_ERROR_MESSAGE = "please only use integers";
    public static final String INVALID_CARD_ERROR_MESSAGE = "invalid credit card";
    public static final String Expired_CARD_ERROR_MESSAGE = "expired credit card";

    public static final String VALID_NAME = ReadExcl.getStringFromCell(10, 'F');
    public static final String VALID_COUNTRY = ReadExcl.getStringFromCell(11, 'F');
    public static final String VALID_CITY = ReadExcl.getStringFromCell(12, 'F');
    public static final String NON_ENGLISH_NAME = ReadExcl.getStringFromCell(13, 'F');
    public static final String NON_ENGLISH_COUNTRY = ReadExcl.getStringFromCell(14, 'F');
    public static final String NON_ENGLISH_CITY = ReadExcl.getStringFromCell(15, 'F');
    public static final String INVALID_COUNTRY = ReadExcl.getStringFromCell(16, 'F');
    public static final String INVALID_CITY = ReadExcl.getStringFromCell(17, 'F');

    private final By nameField = By.id("name");
    private final By countryField = By.id("country");
    private final By cityField = By.id("city");
    private final By creditCardField = By.id("card");
    private final By monthField = By.id("month");
    private final By yearField = By.id("year");

    private final By purchaseButton = By.cssSelector("button[onclick='purchaseOrder()']");

    private void initItemInCartAndGetToPurchaseForm() {
        setDefaultSize();
        driver.get("https://www.demoblaze.com/prod.html?idp_=1");

        // add product to cart
        clickElementSafely(By.xpath("//*[@id=\"tbodyid\"]/div[2]/div/a"));

        assertAlertPresent("Did not add product");
        driver.switchTo().alert().dismiss();

        By cartButton = By.id("cartur");
        clickElementSafely(cartButton);

        By placeOrderButton = By.xpath("//button[text()='Place Order']");

        clickElementSafely(placeOrderButton);

        By popUpIndicator = By.id("orderModalLabel");
        waitForElement(popUpIndicator);
    }

    private void fillFields(
            String strForNameField,
            String strForCountryField,
            String strForCityField,
            String strForCreditCardField,
            String strForMonthField,
            String strForYearField
    ) {
        if (!strForNameField.isEmpty()) {
            driver.findElement(nameField).sendKeys(strForNameField);
        }
        if (!strForCountryField.isEmpty()) {
            driver.findElement(countryField).sendKeys(strForCountryField);
        }
        if (!strForCityField.isEmpty()) {
            driver.findElement(cityField).sendKeys(strForCityField);
        }
        if (!strForCreditCardField.isEmpty()) {
            driver.findElement(creditCardField).sendKeys(strForCreditCardField);
        }
        if (!strForMonthField.isEmpty()) {
            driver.findElement(monthField).sendKeys(strForMonthField);
        }
        if (!strForYearField.isEmpty()) {
            driver.findElement(yearField).sendKeys(strForYearField);
        }

        driver.findElement(purchaseButton).click();
    }

    private boolean randBool() {
        return Math.random() > 0.5;
    }

    private String randString() {
        return UUID.randomUUID().toString();
    }

    private long randCard() {
        return ThreadLocalRandom.current().nextLong(1111_1111_1111_1111L, 9999_9999_9999_9999L);
    }

    private String randValidYear() {
        return String.valueOf(LocalDateTime.now().getYear() + new Random().nextInt(5));
    }

    private String randValidMonth() {
        return String.valueOf(ThreadLocalRandom.current().nextInt(1, 12 + 1));
    }

    @Test
    public void Test_AllEmptyFields() {
        initItemInCartAndGetToPurchaseForm();

        fillFields(
                "",
                "",
                "",
                "",
                "",
                ""
        );

        assertAlertPresent("No alert for missing fields");
        myAssertTrue(
                driver.switchTo().alert().getText().toLowerCase().contains(EMPTY_FIELDS_ERROR_MESSAGE),
                "Missing Empty Fields Error Message!"
        );
    }

    @Test
    public void Test_RandomEmptyFields() {
        List<By> fields = Arrays.asList(
                nameField,
                countryField,
                cityField,
                creditCardField,
                monthField,
                yearField
        );

        // test each field with empty input
        for (int i = 0; i < 6; i++) {
            System.out.println(i);
            initItemInCartAndGetToPurchaseForm();

            driver.findElement(nameField).sendKeys(randString());
            driver.findElement(countryField).sendKeys(VALID_COUNTRY);
            driver.findElement(cityField).sendKeys(VALID_CITY);
            driver.findElement(creditCardField).sendKeys(String.valueOf(randCard()));
            driver.findElement(monthField).sendKeys(randValidMonth());
            driver.findElement(yearField).sendKeys(randValidYear());

            driver.findElement(fields.get(i)).clear();

            driver.findElement(purchaseButton).click();

            assertAlertPresent("No alert for missing field: " + fields.get(i).toString());
            myAssertTrue(
                    driver.switchTo().alert().getText().toLowerCase().contains(EMPTY_FIELDS_ERROR_MESSAGE),
                    "Missing Empty Fields Error Message!"
            );
            driver.switchTo().alert().accept();
        }
    }

    @Test
    public void Test_OnlyNameAndCardFilled() {
        initItemInCartAndGetToPurchaseForm();

        fillFields(
                UUID.randomUUID().toString(),
                "",
                "",
                String.valueOf(randCard()),
                "",
                ""
        );

        assertAlertPresent("No alert for missing fields");
        myAssertTrue(
                driver.switchTo().alert().getText().toLowerCase().contains(EMPTY_FIELDS_ERROR_MESSAGE),
                "Missing Empty Fields Error Message!"
        );
    }

    @Test
    public void Test_NonEnglishCharacters() {
        initItemInCartAndGetToPurchaseForm();

        fillFields(
                NON_ENGLISH_NAME,
                NON_ENGLISH_COUNTRY,
                NON_ENGLISH_CITY,
                String.valueOf(randCard()),
                randValidMonth(),
                randValidYear()
        );

        assertAlertPresent("No alert for non-english characters");
        myAssertTrue(
                driver.switchTo().alert().getText().toLowerCase().contains(WRONG_LANGUAGE_ERROR_MESSAGE),
                "Missing Wrong Language Error Message!"
        );
    }

    @Test
    public void Test_CreditCardWrongLength() {
        initItemInCartAndGetToPurchaseForm();

        fillFields(
                VALID_NAME,
                VALID_COUNTRY,
                VALID_CITY,
                String.valueOf(randCard() / 1000),
                randValidMonth(),
                randValidYear()
        );

        assertAlertPresent("No alert for wrong credit card length");
        myAssertTrue(
                driver.switchTo().alert().getText().toLowerCase().contains(CREDIT_CARD_LENGTH_ERROR_MESSAGE),
                "Missing Credit Card Length Error Message!"
        );
    }

    @Test
    public void Test_NonIntegers() {
        initItemInCartAndGetToPurchaseForm();

        fillFields(
                VALID_NAME,
                VALID_COUNTRY,
                VALID_CITY,
                UUID.randomUUID().toString(),
                UUID.randomUUID().toString(),
                UUID.randomUUID().toString()
        );

        assertAlertPresent("No alert for non integers in integers fields");
        myAssertTrue(
                driver.switchTo().alert().getText().toLowerCase().contains(NON_INTEGERS_ERROR_MESSAGE),
                "Missing Non-Integers Error Message!"
        );
    }

    // algorithm to validate credit card numbers (Luhn algorithm)
    static boolean checkLuhn(String cardNo) {
        int nDigits = cardNo.length();
        int nSum = 0;
        boolean isSecond = false;
        for (int i = nDigits - 1; i >= 0; i--) {
            int d = cardNo.charAt(i) - '0';
            if (isSecond) d = d * 2;
            nSum += d / 10;
            nSum += d % 10;
            isSecond = !isSecond;
        }
        return (nSum % 10 == 0);
    }

    @Test
    public void Test_InvalidCreditCard() {
        initItemInCartAndGetToPurchaseForm();

        String creditCard;
        do {
            creditCard = String.valueOf(randCard());
        } while (checkLuhn(creditCard)); // Make sure card is invalid

        initItemInCartAndGetToPurchaseForm();

        fillFields(
                VALID_NAME,
                VALID_COUNTRY,
                VALID_CITY,
                creditCard,
                randValidMonth(),
                randValidYear()
        );

        assertAlertPresent("No alert for invalid credit card number");
        myAssertTrue(
                driver.switchTo().alert().getText().toLowerCase().contains(INVALID_CARD_ERROR_MESSAGE),
                "Missing Invalid Card Error Message!"
        );
    }

    @Test
    public void Test_ExpiredCard() {
        initItemInCartAndGetToPurchaseForm();

        fillFields(
                VALID_NAME,
                VALID_COUNTRY,
                VALID_CITY,
                String.valueOf(randCard()),
                randValidMonth(),
                String.valueOf(LocalDateTime.now().getYear() - Math.max(new Random().nextInt(5), 1))
        );

        assertAlertPresent("No alert for expired credit card");
        myAssertTrue(
                driver.switchTo().alert().getText().toLowerCase().contains(Expired_CARD_ERROR_MESSAGE),
                "Missing Expired Card Error Message!"
        );
    }

    @Test
    public void Test_InvalidLocation() {
        initItemInCartAndGetToPurchaseForm();

        fillFields(
                VALID_NAME,
                INVALID_COUNTRY,
                INVALID_CITY,
                String.valueOf(randCard()),
                randValidMonth(),
                randValidYear()
        );

        assertAlertPresent("No alert for invalid location");
        myAssertTrue(
                driver.switchTo().alert().getText().toLowerCase().contains(Expired_CARD_ERROR_MESSAGE),
                "Missing Expired Card Error Message!"
        );
    }

    @Test
    public void Test_ValidPurchase() {
        initItemInCartAndGetToPurchaseForm();


        fillFields(
                VALID_NAME,
                VALID_COUNTRY,
                VALID_CITY,
                String.valueOf(randCard()),
                randValidMonth(),
                randValidYear()
        );

        By purchaseCompleteOKButton = By.cssSelector(
                "body > div.sweet-alert.showSweetAlert.visible > div.sa-button-container > div > button"
        );
        clickElementSafely(purchaseCompleteOKButton);

        By cartButton = By.id("cartur");
        clickElementSafely(cartButton);

        By totalPrice = By.id("totalp");
        myAssertTrue(
                driver.findElement(totalPrice).getText().isEmpty(),
                "Purchase Did Not Complete Successfully!"
        );

    }

    public static void main(String[] args) {
        JUnitCore junit = new JUnitCore();
        junit.addListener(new TextListener(System.out));
        Result result = junit.run(Tests_PurchaseForm.class);
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