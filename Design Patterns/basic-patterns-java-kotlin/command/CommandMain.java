package command;

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

// Command design pattern example - finished from last week
public class CommandMain extends Application {
    private final Circle circle = new Circle(50);
    private final Stack<Command> stack = new Stack<>();

    public static void main(String[] args) {

        launch();
    }

    @Override
    public void start(Stage primaryStage) {

        Button bColor = new Button("Color");
        Button bUndo = new Button("Undo");
        bColor.setOnAction(e -> {
            Command cmd = new ConcreteCommand(circle);
            stack.push(cmd);
            cmd.execute();
        });

        bUndo.setOnAction(e -> {
            if (!stack.isEmpty())
                stack.pop().undo();
        });
        HBox hbox = new HBox(40, bColor, bUndo);
        hbox.setPadding(new Insets(50));
        StackPane pane = new StackPane(circle, hbox);
        Scene scene = new Scene(pane, 400, 400);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

}
