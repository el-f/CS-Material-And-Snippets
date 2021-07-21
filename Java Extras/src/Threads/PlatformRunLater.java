package Threads;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;

// Platform.runLater
public class PlatformRunLater extends Application {
    private final Label label = new Label("    Ready...");

    public static void main(String[] args) {
        launch();
    }

    @Override
    public void start(Stage primaryStage) {
        label.setFont(Font.font(30));
        Button button = new Button("GO");
        button.setOnAction(e -> {
            Thread t = new Thread(() -> {
                try {

                    Platform.runLater(() -> label.setText("working..."));
                    Thread.sleep(5000);
                    Platform.runLater(() -> label.setText("finished!"));

                } catch (InterruptedException e1) {
                    // ignore
                }
            });
            t.start();

        });
        VBox vbox = new VBox(50, button, label);
        vbox.setPadding(new Insets(50));
        Scene scene = new Scene(vbox, 300, 300);
        primaryStage.setScene(scene);
        primaryStage.show();

    }

}
