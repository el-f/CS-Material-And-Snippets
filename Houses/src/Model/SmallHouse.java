package Model;

import javafx.scene.paint.Color;

public class SmallHouse extends Building {

    public SmallHouse(boolean roof, boolean windows, boolean door) {
        this();
        setProperty("roof", roof);
        setProperty("windows", windows);
        setProperty("door", door);

    }

    public SmallHouse() {
        changeMainColor(Color.DARKKHAKI);
        numFloors = 2;
    }



}
