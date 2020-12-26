package Program;

import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.geometry.Insets;
import javafx.geometry.Point2D;
import javafx.geometry.Pos;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.transform.Affine;
import javafx.scene.transform.NonInvertibleTransformException;

import java.util.Arrays;
import java.util.Timer;
import java.util.TimerTask;


public class MainView extends VBox {
    private final Affine affine;
    private final Canvas canvas;
    private Simulation simulation;
    private Timer timer;
    private int drawMode = 1;
    static final int SLOW_SPEED = 1000;
    static final int MEDIUM_SPEED = 500;
    static final int FAST_SPEED = 100;
    private int currentSpeed = MEDIUM_SPEED;
    private boolean running = false;

    void pause() {
        running = false;
        timer.cancel();
    }

    void resume() {
        timer.cancel();
        running = true;
        timer = new Timer();
        timer.schedule(new TimerTask() {
                           @Override
                           public void run() {
                               // Using runLater to avoid thread crashes.
                               Platform.runLater(() -> {
                                   simulation.step();
                                   draw();
                               });
                           }
                       }, 0, currentSpeed
        );
    }

    void changeSpeed(int speed) {
        currentSpeed = speed;
        if (running) resume();

        else pause();
    }

    public MainView() {
        timer = new Timer();

        Button stepButton = new Button("Step");
        stepButton.setOnAction(actionEvent -> {
            simulation.step();
            draw();
        });


        Button runButton = new Button("Run");
        runButton.setOnAction(event -> resume());
        Button slowButton = new Button("Slow Speed");
        slowButton.setOnAction(event -> changeSpeed(SLOW_SPEED));
        Button mediumButton = new Button("Medium Speed");
        mediumButton.setOnAction(event -> changeSpeed(MEDIUM_SPEED));
        Button fastButton = new Button("Fast Speed");
        fastButton.setOnAction(event -> changeSpeed(FAST_SPEED));

        HBox runButtons = new HBox(runButton, slowButton, mediumButton, fastButton);

        Button pauseButton = new Button("Pause");
        pauseButton.setOnAction(event -> pause());

        Label label = new Label("Keys: D-Draw E-Erase T-Toggle");


        canvas = new Canvas(640, 480);
        // Using runLater to avoid thread crashes.
        canvas.setOnMousePressed(event -> Platform.runLater(() -> handleDraw(event)));
        canvas.setOnMouseDragged(event -> Platform.runLater(() -> handleDraw(event)));

        setOnKeyPressed(this::onKeyPressed);

        simulation = new Simulation((int) canvas.getWidth() / 20, (int) canvas.getHeight() / 20);
        getChildren().addAll(
                stepButton,
                runButtons,
                pauseButton,
                label,
                canvas
        );
//        Arrays.asList(stepButton, runButton, pauseButton, label)
//                .forEach(button -> button.setPadding(new Insets(5, 5, 5, 5)));
//        setSpacing(5);

        affine = new Affine();
        affine.appendScale(canvas.getWidth() / simulation.width, canvas.getHeight() / simulation.height - 3.9);

        for (int x = 0; x < simulation.width; x++) {
            for (int y = 0; y < simulation.height; y++) {
                if (x % 2 != 0 && x % (y + 1) / 2 != 0)
                    simulation.setAlive(x, y);
            }
        }
    }

    private void onKeyPressed(KeyEvent keyEvent) {
        if (keyEvent.getCode() == KeyCode.D) drawMode = 1;
        else if (keyEvent.getCode() == KeyCode.E) drawMode = 0;
        else if (keyEvent.getCode() == KeyCode.T) drawMode = 2;
    }

    private void handleDraw(MouseEvent mouseEvent) {
        double mx = mouseEvent.getX();
        double my = mouseEvent.getY();

        try {
            final Point2D simCoord = affine.inverseTransform(mx, my);
            int simX = (int) Math.floor(simCoord.getX());
            int simY = (int) Math.floor(simCoord.getY());
            switch (drawMode) {
                case 0:
                    simulation.setDead(simX, simY);
                    break;
                case 1:
                    simulation.setAlive(simX, simY);
                    break;
                case 2:
                    simulation.toggleState(simX, simY);
                    break;
            }
            draw();
        } catch (NonInvertibleTransformException e) {
            e.printStackTrace();
        }
    }

    public void draw() {
        GraphicsContext g = canvas.getGraphicsContext2D();
        g.setFill(Color.LIGHTGRAY);
        g.fillRect(0, 0, canvas.getWidth(), canvas.getWidth());
        g.setTransform(affine);
        g.setFill(Color.BLACK);

        for (int x = 0; x < simulation.width; x++) {
            for (int y = 0; y < simulation.height; y++) {
                if (simulation.getCellValue(x, y) == 1)
                    g.fillRect(x, y, 1, 1);
            }
        }

        g.setLineWidth(0.05f);
        g.setStroke(Color.LIGHTGRAY);
        for (int x = 0; x <= canvas.getWidth(); x++) {
            g.strokeLine(x, 0, x, canvas.getWidth());
        }
        for (int y = 0; y <= canvas.getHeight(); y++) {
            g.strokeLine(0, y, canvas.getHeight(), y);
        }
    }
}
