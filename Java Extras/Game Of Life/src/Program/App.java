package Program;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class App extends Application {

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setOnCloseRequest(r -> {
            Platform.exit();
            System.exit(0);
        });

        MainView mainView = new MainView();
        Scene scene = new Scene(mainView, 950, 855);
        primaryStage.setTitle("Game of Life");
        primaryStage.setScene(scene);
        primaryStage.show();
        mainView.draw();
    }

    public static void main(String[] args) {
        launch();
    }
}
