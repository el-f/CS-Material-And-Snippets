package singleton;

public class IdGenerator {
    private static final IdGenerator[] _instance = new IdGenerator[2];
    private int id;

    private IdGenerator() {
        this.id = 0;
    }

    public int getId() {
        return id;
    }

    public int getNext() {
        return ++id;
    }

    @Override
    public String toString() {
        return "IdGenerator [id=" + id + "]";
    }

    public static IdGenerator getInstance(int i) {
        if (_instance[i] == null)
            _instance[i] = new IdGenerator();
        return _instance[i];
    }


}
