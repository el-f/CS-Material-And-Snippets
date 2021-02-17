package decorator;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class ConcreteDecoratorB_Fill extends Decorator {

    public ConcreteDecoratorB_Fill(Component component) {
        super(component);
    }

    @Override
    public void operation() {
        super.operation();
        addedBehavior_Fill();
    }

    @Override
    public Circle getCircle() {
        return super.getCircle();
    }

    private void addedBehavior_Fill() {
        getCircle().setFill(Color.color(Math.random(), Math.random(), Math.random()));
    }

}
