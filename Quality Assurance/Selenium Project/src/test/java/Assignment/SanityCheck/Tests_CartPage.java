package Assignment.SanityCheck;

import Assignment.SeleniumTest;
import org.junit.Test;
import org.junit.internal.TextListener;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.openqa.selenium.By;


public class Tests_CartPage extends SeleniumTest {

    public static final String EMPTY_CART = "can't place order";

    private int getProductPriceFromPage() {
        By prodPrice = By.xpath("//*[@id=\"tbodyid\"]/h3");
        waitForElement(prodPrice);

        return Integer.parseInt(
                driver.findElement(prodPrice).getText().replaceAll("[^\\d.]", "") //remove non digits
        );
    }

    private void clickAddToCart() {
        By addToCartButton = By.xpath("//*[@id=\"tbodyid\"]/div[2]/div/a");
        waitForElement(addToCartButton);
        driver.findElement(addToCartButton).click();

        assertAlertPresent("Did not add to cart / no indication");
        driver.switchTo().alert().accept();
    }

    private void clickPlaceOrder() {
        By placeOrder = By.xpath("//*[@id=\"page-wrapper\"]/div/div[2]/button");
        clickElementSafely(placeOrder);
    }

    private void clickCartPage(){
        driver.findElement(By.id("cartur")).click();
    }

    @Test
    public void Test_AddProductToCart() {
        initDefaults();
        //add product
        clickElementSafely(By.cssSelector("#tbodyid > div:nth-child(1) > div > a > img"));
        clickAddToCart();

        clickCartPage();
        String totalPrice1 = driver.findElement(By.id("totalp")).getText();

        clickPlaceOrder();

        String totalPrice2 = driver.findElement(By.id("totalm")).getText();
        myAssertEquals(
                totalPrice1, totalPrice2,
                "Total price doesn't match product price"
        );
    }

    @Test
    public void Test_DeleteProductFromCart() {
        initDefaults();
        //add first product
        clickElementSafely(By.cssSelector("#tbodyid > div:nth-child(5) > div > div > h4 > a"));
        clickAddToCart();

        //add second product
        driver.findElement(By.cssSelector("#nava > img")).click();
        clickElementSafely(By.cssSelector("#tbodyid > div:nth-child(8) > div > div > h4 > a"));
        clickAddToCart();

        //get second product price
        int secondProductPrice = getProductPriceFromPage();

        driver.findElement(By.id("cartur")).click();
        //get original total price
        By tPrice = By.id("totalp");
        waitForElement(tPrice);
        int originalTotalPrice = Integer.parseInt(driver.findElement(tPrice).getText());

        //delete first product
        clickElementSafely(By.cssSelector("#tbodyid > tr:nth-child(2) > td:nth-child(4) > a"));

        //get new total price
        By tPrice2 = By.cssSelector("#totalp");
        waitForElement(tPrice2);
        int finaleTotalPrice = Integer.parseInt(driver.findElement(tPrice2).getText());
        myAssertEquals(//check if new total price updated correctly
                secondProductPrice + finaleTotalPrice, originalTotalPrice,
                "Total price doesn't equals products in cart price sum"
        );

    }

    @Test
    public void Test_PlaceEmptyOrder() {
        initDefaults();
        clickCartPage();

        clickPlaceOrder();

        assertAlertPresent("No alert for / Placed: Empty Order");

        myAssertTrue(
                driver.switchTo().alert().getText().toLowerCase().contains(EMPTY_CART.toLowerCase()),
                "Missing empty cart message"
        );
    }

    @Test
    public void Test_ShowProducts() {
        initDefaults();
        //add first product
        clickElementSafely(By.cssSelector("#tbodyid > div:nth-child(5) > div > a > img"));
        clickAddToCart();

        //get first product price
        int firstProductPrice = getProductPriceFromPage();

        //add second product
        driver.findElement(By.cssSelector("#nava > img")).click();
        clickElementSafely(By.cssSelector("#tbodyid > div:nth-child(8) > div > a > img"));
        clickAddToCart();

        //get second product price
        int secondProductPrice = getProductPriceFromPage();

        clickCartPage();

        By tPrice1 = By.cssSelector("#totalp");//products price sum
        waitForElement(tPrice1);
        int intTotalPrice = Integer.parseInt(driver.findElement(tPrice1).getText());
        myAssertEquals(
                intTotalPrice, secondProductPrice + firstProductPrice,
                "Total price doesn't match products price sum"
        );

        int prodDisplayPrice1 = Integer.parseInt(
                driver.findElement(By.cssSelector("#tbodyid > tr:nth-child(1) > td:nth-child(3)")).getText()
        );
        int prodDisplayPrice2 = Integer.parseInt(
                driver.findElement(By.cssSelector("#tbodyid > tr:nth-child(2) > td:nth-child(3)")).getText()
        );

        myAssertEquals(
                prodDisplayPrice1, firstProductPrice,
                "First product price doesn't match price in product page"
        );
        myAssertEquals(
                prodDisplayPrice2, secondProductPrice,
                "Second product price doesn't match price in product page"
        );

        waitForElement(tPrice1);
        intTotalPrice = Integer.parseInt(driver.findElement(tPrice1).getText());
        myAssertEquals(
                intTotalPrice, firstProductPrice + secondProductPrice,
                "Total price doesn't match expectations"
        );
    }

    public static void main(String[] args) {
        JUnitCore junit = new JUnitCore();
        junit.addListener(new TextListener(System.out));
        Result result = junit.run(Tests_CartPage.class);
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