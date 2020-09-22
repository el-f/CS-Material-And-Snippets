package Lambda;

interface Cab {// when an interface has exactly 1 abstract method it's called functional
	void bookCab(); // abstract of cause
}

interface Cab2 {// when an interface has exactly 1 abstract method it's called functional
	void bookCab(String source, String dest); // abstract of cause
}

interface Cab3 {// when an interface has exactly 1 abstract method it's called functional
	int bookCab(String source, String dest); // abstract of cause
}

//class Uber implements Cab {
//	public void bookCab() {
//		System.out.println("uber booked!");
//	}
//}
public class LambdaCab {

	static int instanceVar = 10;

	static int sVar = 100;

	public static void main(String[] args) {

		// 1.
//		Cab cab = new Uber(); //polymorphic
//		cab.bookCab();
		// 2.
//		Cab cab = new Cab() { // anonymous class
//
//			@Override
//			public void bookCab() {
//				System.out.println("uber booked!");
//			}
//		};
//		cab.bookCab();
		// 3.
		Cab cab = () -> { // Lambda
			System.out.println("uber booked!");
		};
		cab.bookCab();

		Cab2 cab2 = (s, d) -> System.out.println("going from " + s + " to " + d);
		cab2.bookCab("tel-aviv", "jeruslaem");

		Cab3 cab3 = (s, d) -> {
			System.out.println("going from " + s + " to " + d);
			System.out.println("insVar is: " + instanceVar);
			return 180;
		};
		System.out.println(cab3.bookCab("haifa", "LA"));

	}

}
