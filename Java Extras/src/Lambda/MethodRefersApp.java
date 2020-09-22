package Lambda;

interface Calculator {
	void add(int num1, int num2);
}

class Calc {
	public static void addSomething(int num1, int num2) {
		System.out.println(num1 + " + " + num2 + " = " + (num1 + num2));
	}

	public void letsAdd(int num1, int num2) {
		System.out.println(num1 + " + " + num2 + " = " + (num1 + num2));
	}
}

interface Messenger {
	Message getMessage(String msg);
}

class Message {
	Message(String msg) {
		System.out.println(">> msg is: " + msg);
	}
}

public class MethodRefersApp {
	public static void main(String[] args) {
		Calc.addSomething(10, 20);
		Calculator cRef = Calc::addSomething; // reference to a static method
		cRef.add(11, 14);

		Calc calc = new Calc();
		Calculator cRef2 = calc::letsAdd; // method refer
		cRef2.add(13, 24);

		// refer to constructor
		Messenger mRef = Message::new;
		mRef.getMessage("this is a nice message");
	}

}