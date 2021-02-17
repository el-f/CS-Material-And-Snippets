package observer;

import java.util.HashSet;
import java.util.Set;

public class MyButton {

    private Set<Observer> set = new HashSet<>();

    public void attach(Observer o) {
        set.add(o);
    }

    public void push() {
        notify_button();
    }

    private void notify_button() {
        for (Observer o : set)
            o.update();
    }
}
