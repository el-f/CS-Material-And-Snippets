package observer;

// Observer design pattern with different objects
public class ObserverMain {

	public static void main(String[] args) {
		MyButton button = new MyButton();
		button.attach(new Student("Bamba", 89));
		button.attach(new Student("Kinder Bueno", 55));
		button.attach(new Lecturer("Bisli"));
		
		button.push();
	}

}
