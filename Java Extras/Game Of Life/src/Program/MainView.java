package Program;

import javafx.application.Platform;
import javafx.geometry.Point2D;
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

import java.util.Timer;
import java.util.TimerTask;


public class MainView extends VBox {
    private final Affine affine;
    private final Canvas canvas;
    private Simulation simulation;
    private Timer timer;
    private int drawMode = DRAW_MODE;
    static final int SLOW_SPEED = 500;
    static final int FAST_SPEED = 50;
    static final int SONIC = 1;
    private int currentSpeed = FAST_SPEED;
    private boolean running = false;
    private final Label drawIndicator = new Label("D - Draw"),
            toggleIndicator = new Label("T - Toggle"),
            eraseIndicator = new Label("E - Erase");
    public static final int ERASE_MODE = 0, DRAW_MODE = 1, TOGGLE_MODE = 2;

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
                       }, 15, currentSpeed
        );
    }

    void changeSpeed(int speed) {
        currentSpeed = speed;
        if (running) resume();
        else pause();
    }

    void reset() {
        simulation = new Simulation(Simulation.DEFAULT_STARTER);
        simulation.step();
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

        Slider slider = new Slider();
        slider.setValue(currentSpeed);
        slider.setMax(SLOW_SPEED);
        slider.setMin(SONIC);
        slider.setShowTickLabels(true);
        slider.setShowTickMarks(true);
        slider.valueProperty().addListener((OBS, OLD, NEW) -> changeSpeed(NEW.intValue()));
        slider.setMinWidth(650);

        HBox runBox = new HBox(runButton, new Label("Delay Between Steps (ms) : "), slider);
        runBox.setSpacing(10);
        setSpacing(10);

        Button pauseButton = new Button("Pause");
        pauseButton.setOnAction(event -> pause());

        Button resetButton = new Button("Reset");
        resetButton.setOnAction(event -> {
            reset();
            draw();
        });

        Button clearButton = new Button("Clear");
        clearButton.setOnAction(event -> {
            simulation.clear();
            draw();
        });

        HBox pause_reset = new HBox(pauseButton, resetButton, clearButton);
        pause_reset.setSpacing(10);

        HBox keys = new HBox(new Label("Draw Mode Keys: "), drawIndicator, eraseIndicator, toggleIndicator);
        keys.setSpacing(10);

        canvas = new Canvas(950, 708);
        // Using runLater to avoid thread crashes.
        canvas.setOnMousePressed(event -> Platform.runLater(() -> handleDraw(event)));
        canvas.setOnMouseDragged(event -> Platform.runLater(() -> handleDraw(event)));

        setOnKeyPressed(this::onKeyPressed);

        getChildren().addAll(
                stepButton,
                pause_reset,
                runBox,
                keys,
                canvas
        );

        reset();
        System.out.println("Initialized simulation...");
        System.out.println("Height: "+ simulation.height + ", Width: " + simulation.width);
        affine = new Affine();
        affine.appendScale(canvas.getWidth() / simulation.width, canvas.getHeight() / simulation.height);
        updateModeIndicator();
    }

    private void updateModeIndicator() {
        switch (drawMode) {
            case DRAW_MODE:
                drawIndicator.setTextFill(Color.RED);
                eraseIndicator.setTextFill(Color.BLACK);
                toggleIndicator.setTextFill(Color.BLACK);
                break;
            case ERASE_MODE:
                drawIndicator.setTextFill(Color.BLACK);
                eraseIndicator.setTextFill(Color.RED);
                toggleIndicator.setTextFill(Color.BLACK);
                break;
            case TOGGLE_MODE:
                drawIndicator.setTextFill(Color.BLACK);
                eraseIndicator.setTextFill(Color.BLACK);
                toggleIndicator.setTextFill(Color.RED);
                break;
        }
    }

    private void onKeyPressed(KeyEvent keyEvent) {
        if (keyEvent.getCode() == KeyCode.D) drawMode = DRAW_MODE;
        else if (keyEvent.getCode() == KeyCode.E) drawMode = ERASE_MODE;
        else if (keyEvent.getCode() == KeyCode.T) drawMode = TOGGLE_MODE;

        updateModeIndicator();
    }

    private void handleDraw(MouseEvent mouseEvent) {
        try {
            final Point2D simCoord = affine.inverseTransform(mouseEvent.getX(), mouseEvent.getY());
            int simX = (int) Math.floor(simCoord.getX());
            int simY = (int) Math.floor(simCoord.getY());
            switch (drawMode) {
                case ERASE_MODE:
                    simulation.setDead(simY, simX);
                    break;
                case DRAW_MODE:
                    simulation.setAlive(simY, simX);
                    break;
                case TOGGLE_MODE:
                    simulation.toggleState(simY, simX);
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
        for (int r = 0; r < simulation.height; r++) {
            for (int c = 0; c < simulation.width; c++) {
                if (simulation.getCellValue(r, c) == 1)
                    g.fillRect(c, r, 1, 1);
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
