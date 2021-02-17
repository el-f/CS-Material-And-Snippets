package decorator;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

// Decorator example. (Simple circle with only stroke, decorated
// with border with random colors, and with background with random color)
public class DecoratorMain extends Application {

    public static void main(String[] args) {
        launch();
    }

    @Override
    public void start(Stage primaryStage) {

        Button bOperation = new Button("bOperation");
        bOperation.setDefaultButton(true);
        HBox hbox = new HBox(30, bOperation);
        hbox.setPadding(new Insets(50));
        StackPane pane = new StackPane(hbox);

        bOperation.setOnAction(e -> {
            //Component c = new ConcreteCircle(70);
            //Component c = new ConcreteDecoratorA_Border(new ConcreteCircle(70));
            Component c = new ConcreteDecoratorB_Fill(new ConcreteDecoratorA_Border(new ConcreteCircle(70)));
            //Component c = new ConcreteDecoratorB_Fill(new ConcreteCircle(70));
            c.operation();
            pane.getChildren().add(c.getCircle());

        });


        Scene scene = new Scene(pane, 450, 450);
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);
        primaryStage.show();
    }

}
