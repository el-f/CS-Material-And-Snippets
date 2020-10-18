package Model;

import javafx.scene.paint.Color;

public class TallBuilding extends Building {

    public TallBuilding(boolean roof, boolean windows, boolean door) {
        this();
        setProperty("roof", roof);
        setProperty("windows", windows);
        setProperty("door", door);
    }

    public TallBuilding() {
        changeBodyRectangle(110, 90, 140, 320);
        changeMainColor(Color.SADDLEBROWN);
        changeRoof(110, 90, 140, 50);
    }
}
