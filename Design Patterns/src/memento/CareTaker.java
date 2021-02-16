package memento;

import java.util.ArrayList;
import java.util.List;

public class CareTaker {

    private final List<Memento> list;

    public CareTaker() {
        this.list = new ArrayList<>();
    }

    public void save(Memento pm) {
        list.add(pm);
    }

    public void load(int index) {
        list.get(index).load();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Saves:\n");
        list.forEach(pm -> sb.append(pm).append("\n"));
        return sb.toString();
    }


}
