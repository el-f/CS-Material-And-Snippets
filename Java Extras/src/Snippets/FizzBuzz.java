package Snippets;

public class FizzBuzz {
    public static void main(String[] args) {
        fizzBuzzV2();
        /*---------*/
        fizzBuzzV1();
    }

    public static void fizzBuzzV2() {
        for (int i = 1; i <= 100; i++) {
            String str = "";
            if (i % 3 == 0) str += "fizz";
            if (i % 5 == 0) str += "buzz";
            if (str.equals("")) str += i;
            System.out.println(str);
        }
    }

    public static void fizzBuzzV1() {
        for (int i = 1; i < 100; i++) {
            System.out.println(fizzy(i));
        }
    }

    private static String fizzy(int num) {
        int a = 3;
        int b = 5;
        if (num % a == 0 && num % b == 0)
            return "fizzbuzz";
        if (num % a == 0)
            return "fizz";
        if (num % b == 0)
            return "buzz";
        return num + "";
    }
}