package Model;

import javafx.scene.Group;
import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.Rectangle;

import java.util.Arrays;


public class Castle extends Building {
    private Rectangle leftTower;
    private Rectangle rightTower;
    private Polygon rightTowerRoof;

    public Castle() {
        changeMainColor(Color.DARKGRAY);
        changeBodyRectangle(100, 200, 160, 150);
        leftTower = new Rectangle(60, 120, 40, 230);
        leftTower.setFill(bodyColor);
        leftTower.setStroke(Color.BLACK);
        rightTower = new Rectangle(260, 120, 40, 230);
        rightTower.setFill(bodyColor);
        rightTower.setStroke(Color.BLACK);
        changeRoof((int) leftTower.getX(), (int) leftTower.getY(), (int) leftTower.getWidth(), (int) leftTower.getY());
        double[] points = {(int) rightTower.getX(), (int) rightTower.getY(), rightTower.getX() + rightTower.getWidth() / 2, 0, rightTower.getX() + (int) rightTower.getWidth(), rightTower.getY()};
        rightTowerRoof = new Polygon(points);
        rightTowerRoof.setFill(roofColor);
        rightTowerRoof.setStroke(roof.getStroke());
        numFloors = 1;
    }

    public Castle(boolean roof, boolean windows, boolean door) {
        this();
        setProperty("roof", roof);
        setProperty("windows", windows);
        setProperty("door", door);
    }

    public void show(Group root) {
        root.getChildren().add(body);
        root.getChildren().addAll(rightTower, leftTower);
        if (hasRoof) {
            root.getChildren().addAll(roof, rightTowerRoof);
        }
        if (hasWindows) {
            root.getChildren().addAll(windows);
        }
        if (hasDoor) {
            setDoor();
            root.getChildren().add(door);
        }
    }

    public void changeRoofColor(String _roofColor) {
        roofColor = Color.valueOf(_roofColor);
        roof.setFill(roofColor);
        rightTowerRoof.setFill(roofColor);
    }

    @Override
    public void setWindows() {
        super.setWindows();
        int hGap, vGap, width, height;
        hGap = width = (int) leftTower.getWidth() / 3;
        vGap = (int) leftTower.getHeight() / 8;
        height = vGap * 2;
        Rectangle ltw = new Rectangle(leftTower.getX() + hGap, leftTower.getY() + vGap, width, height);
        Rectangle rtw = new Rectangle(rightTower.getX() + hGap, rightTower.getY() + vGap, width, height);
        Rectangle ltbw = new Rectangle(leftTower.getX() + hGap, leftTower.getY() + 4 * vGap, width, height);
        Rectangle rtbw = new Rectangle(rightTower.getX() + hGap, rightTower.getY() + 4 * vGap, width, height);
        windows.addAll(Arrays.asList(ltw, rtw, ltbw, rtbw));
    }
}
