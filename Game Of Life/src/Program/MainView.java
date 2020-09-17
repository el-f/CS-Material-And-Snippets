package Program;

import javafx.geometry.Point2D;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.transform.Affine;
import javafx.scene.transform.NonInvertibleTransformException;


public class MainView extends VBox {
    private final Affine affine;
    private final Canvas canvas;
    private Simulation simulation;
    boolean run;

    private int drawMode = 1;

    public MainView() {
        Button stepButton = new Button("step");
        Button runBtn = new Button("Run");
        runBtn.setOnAction(event -> {
            run = true;
            while (run) {
                simulation.step();
                draw();
//                try {
////                    Thread.sleep(5000);
//                } catch (InterruptedException e) {
//                    e.printStackTrace();
//                }
            }
        });
        Button stopBtn = new Button("Stop");
        stopBtn.setOnAction(event -> run = false);
        Label label = new Label("D-Draw E-Erase T-Toggle");
        stepButton.setOnAction(actionEvent -> {
            simulation.step();
            draw();
        });
        canvas = new Canvas(640, 400);
        canvas.setOnMousePressed(this::handleDraw);
        canvas.setOnMouseDragged(this::handleDraw);

        setOnKeyPressed(this::onKeyPressed);

        simulation = new Simulation((int) canvas.getWidth() / 20, (int) canvas.getHeight() / 20);
        getChildren().addAll(stepButton, runBtn, stopBtn, label, canvas);

        affine = new Affine();
        affine.appendScale(canvas.getWidth() / simulation.width, canvas.getHeight() / simulation.height);

        for (int x = 0; x < simulation.width; x++) {
            for (int y = 0; y < simulation.height; y++) {
                if (x % 2 != 0 && x % (y + 1) / 2 != 0)
                    simulation.setAlive(x, y);
            }
        }
    }

    private void onKeyPressed(KeyEvent keyEvent) {
        if (keyEvent.getCode() == KeyCode.D) {
            drawMode = 1;
        } else if (keyEvent.getCode() == KeyCode.E) {
            drawMode = 0;
        } else if (keyEvent.getCode() == KeyCode.T)
            drawMode = 2;
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
