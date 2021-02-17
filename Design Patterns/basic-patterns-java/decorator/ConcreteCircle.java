package decorator;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class ConcreteCircle extends Circle implements Component {

    public ConcreteCircle(double radius) {
        super(radius);
    }

    @Override
    public void operation() {
        this.setFill(Color.TRANSPARENT);
        this.setStroke(Color.BLACK);
    }

    @Override
    public Circle getCircle() {
        return this;
    }

}
