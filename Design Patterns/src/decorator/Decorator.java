package decorator;

import javafx.scene.shape.Circle;

public abstract class Decorator implements Component {
    private Component component;

    public Decorator(Component component) {
        this.component = component;
    }

    @Override
    public void operation() {
        component.operation();
    }

    @Override
    public Circle getCircle() {
        return component.getCircle();
    }
}
