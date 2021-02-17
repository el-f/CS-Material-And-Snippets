package memento.circle;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class MyCircle extends Circle {
    public MyCircle(double radius) {
        super(radius);
    }

    public void setMemento(Memento m) {
        this.setFill(m.getColor());
    }

    public Memento createMemento() {
        return new Memento((Color) this.getFill());
    }

    public static class Memento {
        private final Color color;

        private Memento(Color color) {
            this.color = color;
        }

        private Color getColor() {
            return color;
        }
    }
}
