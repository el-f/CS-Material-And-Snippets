package observer;

public class Student implements Observer{
	private String name;
	private int grade;

	public Student(String name, int grade) {
		super();
		this.name = name;
		this.grade = grade;
	}

	@Override
	public String toString() {
		return name + ", " + grade;
	}

	@Override
	public void update() {
		System.out.println("Hi from student: " + name);
		
	}
}
