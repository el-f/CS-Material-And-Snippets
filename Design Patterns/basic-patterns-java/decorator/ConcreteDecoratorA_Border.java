package decorator;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class ConcreteDecoratorA_Border extends Decorator {

    public ConcreteDecoratorA_Border(Component component) {
        super(component);
    }

    @Override
    public void operation() {
        super.operation();
        addedBehavior_Border();
    }

    @Override
    public Circle getCircle() {
        return super.getCircle();
    }

    private void addedBehavior_Border() {
        getCircle().setStrokeWidth(6);
        getCircle().setStroke(Color.color(Math.random(), Math.random(), Math.random()));
    }

}
