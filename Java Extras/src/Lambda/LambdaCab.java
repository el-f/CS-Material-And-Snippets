package Lambda;

// when an interface has exactly 1 (abstract) method it's called functional

interface Cab {
    void bookCab();
}

interface Cab2 {
    void bookCab(String source, String dest);
}

interface Cab3 {
    int bookCab(String source, String dest);
}

public class LambdaCab {

    public static void main(String[] args) {

//        1.
        Cab polyCab = new Uber(); //polymorphic
        polyCab.bookCab();

//        2.
        Cab anonCab = new Cab() { // anonymous class
            @Override
            public void bookCab() {
                System.out.println("uber booked!");
            }
        };
        anonCab.bookCab();

//        3.
        Cab cab = () -> System.out.println("uber booked!"); // Lambda
        cab.bookCab();

        Cab2 cab2 = (s, d) -> System.out.println("going from " + s + " to " + d);
        cab2.bookCab("tel-aviv", "jeruslaem");

        Cab3 cab3 = (s, d) -> {
            System.out.println("going from " + s + " to " + d);
            return 180;
        };
        System.out.println(cab3.bookCab("haifa", "LA"));
    }

    private static class Uber implements Cab {
        @Override
        public void bookCab() {
            System.out.println("uber booked!");
        }
    }

}
