package command;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class ConcreteCommand implements Command {

    private final Circle circle;
    private Color previousColor;

    public ConcreteCommand(Circle circle) {
        this.circle = circle;
    }

    @Override
    public void execute() {
        previousColor = (Color) circle.getFill();
        circle.setFill(Color.color(Math.random(), Math.random(), Math.random()));
    }

    @Override
    public void undo() {
        circle.setFill(previousColor);
    }

}
