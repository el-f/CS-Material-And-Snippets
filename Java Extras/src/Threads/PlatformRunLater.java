package Threads;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
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
        VBox vbox = new VBox(50, button, label);
        vbox.setAlignment(Pos.CENTER);
        button.setOnAction(event -> {
            Thread t = new Thread(() -> {
                try {
                    int countDown = 5;
                    Platform.runLater(() -> label.setText("working:\t" + countDown));
                    indicateProgress(label, countDown);
                    Thread.sleep(countDown * 1000);
                    Platform.runLater(() -> label.setText("finished!"));

                    addExitButton(vbox);
                    vbox.getChildren().get(0).setDisable(true);
                } catch (InterruptedException e1) {
                    // ignore
                }
            });
            t.start();
        });

        Scene scene = new Scene(vbox, 300, 300);
        primaryStage.setScene(scene);
        primaryStage.show();

    }

    @SuppressWarnings("all")
    void indicateProgress(Label label, int countDown) {
        new Thread(() -> {
            for (char cd = Character.forDigit(countDown, 10); cd > '0'; cd--) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    // ignore
                }
                char finalCd = cd;
                Platform.runLater(() -> label.setText(label.getText().replace(finalCd, (char) (finalCd - 1))));
            }
        }).start();
    }

    void addExitButton(VBox vbox) {
        Button exitBtn = new Button("Exit");
        exitBtn.setOnAction(event -> {
            Platform.exit();
            System.exit(0);
        });
        Platform.runLater(() -> vbox.getChildren().add(exitBtn));
    }

}
