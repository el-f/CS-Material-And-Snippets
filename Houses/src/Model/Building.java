package Model;

import javafx.scene.Group;
import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.Rectangle;

import java.util.ArrayList;


public class Building {
    protected boolean hasRoof, hasWindows, hasDoor;
    protected Rectangle body, door;
    protected ArrayList<Rectangle> windows;
    protected Color bodyColor, roofColor;
    protected Polygon roof;
    protected int numWindowsInRow, numFloors;

    public Building() {
        windows = new ArrayList<>();
        body = new Rectangle(50, 50, 200, 200);
        bodyColor = Color.CYAN;
        roofColor = Color.RED;
        body.setFill(bodyColor);
        body.setStroke(Color.BLACK);
        hasRoof = false;
        hasWindows = false;
        hasDoor = false;
        roof = new Polygon(body.getX(), body.getY(), body.getX() + body.getWidth(), body.getY(), body.getX() + 100, body.getY() - 100);
        roof.setFill(Color.RED);
        roof.setStroke(Color.BLACK);
        door = new Rectangle();
        numWindowsInRow = 2;
        numFloors = 5;
    }

    public void changeMainColor(Color c) {
        bodyColor = c;
        body.setFill(bodyColor);
    }

    public void changeBodyRectangle(int x, int y, int width, int height) {
        body.setX(x);
        body.setY(y);
        body.setWidth(width);
        body.setHeight(height);
    }

    public void changeRoof(int left, int top, int width, int height) {
        Double[] Points = {(double) left, (double) top,
                (double) left + width / 2, (double) top - height,
                (double) left + width, (double) top};
        roof.getPoints().clear();
        roof.getPoints().addAll(Points);
    }

    public void show(Group root) {
        root.getChildren().add(body);
        if (hasRoof) {
            root.getChildren().add(roof);
        }
        if (hasDoor) {
            setDoor();
            root.getChildren().add(door);
        }
    }

    public void setWindows() {
        int height = (int) body.getWidth() / 5, width = (int) body.getWidth() / 5, hGap = (int) body.getWidth() / 5,
                vGap = (int) body.getWidth() / 5;
        for (int floors = 0; floors < numFloors; floors++) {
            for (int wnds = 0; wnds < numWindowsInRow; wnds++) {
                Rectangle window = new Rectangle(
                        body.getX() + (wnds % numWindowsInRow + 1) * hGap + width * (wnds % numWindowsInRow),
                        body.getY() + (floors) * vGap + height * (floors+1), width, height);
                window.setFill(Color.PERU);
                window.setStroke(Color.BLACK);
                windows.add(window);
            }
        }
    }

    public ArrayList<Rectangle> getWindows() {
        return windows;
    }

    public int getNumWindows() {
        return windows.size();
    }

    protected void setDoor() {
        door.setWidth(body.getWidth() / 6);
        door.setX(body.getX() + body.getWidth() / 2 - door.getWidth() / 2);
        door.setHeight(45);
        door.setY(body.getY() + body.getHeight() - door.getHeight());
        door.setFill(Color.DARKGOLDENROD);
    }

    public void setProperty(String property, boolean value) {
        switch (property) {
            case "roof":
                hasRoof = value;
                break;
            case "windows":
                hasWindows = value;
                setWindows();
                break;
            case "door":
                hasDoor = value;
                break;
        }
    }

    public void changeRoofColor(String _roofColor) {
        roofColor = Color.valueOf(_roofColor);
        roof.setFill(roofColor);
    }


}
