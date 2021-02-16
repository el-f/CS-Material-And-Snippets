package memento.circle;

import java.util.Stack;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;

// Memento design pattern - as Q1, but this time with memento.
public class CircleMementoMain extends Application {
    private final MyCircle circle = new MyCircle(50);
    private final Stack<MyCircle.Memento> stack = new Stack<>();

    public static void main(String[] args) {
        launch();
    }

    @Override
    public void start(Stage primaryStage) {
        Button bColor = new Button("Color");
        Button bUndo = new Button("Undo");
        bColor.setOnAction(e -> {
            stack.push(circle.createMemento());
            circle.setFill(Color.color(Math.random(), Math.random(), Math.random()));
        });

        bUndo.setOnAction(e -> {
            if (!stack.isEmpty())
                circle.setMemento(stack.pop());
        });
        HBox hbox = new HBox(40, bColor, bUndo);
        hbox.setPadding(new Insets(50));
        StackPane pane = new StackPane(circle, hbox);
        Scene scene = new Scene(pane, 400, 400);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

}
