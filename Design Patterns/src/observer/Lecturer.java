package observer;

public class Lecturer implements Observer {
    private final String name;

    public Lecturer(String name) {
        super();
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public void update() {
        System.out.println("Hello from lecturer: " + name);

    }

}
