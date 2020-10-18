package Model;


import javafx.scene.Group;

public class Model {
    private Building theBuilding;

    public Model() {
        theBuilding = new TallBuilding();
    }

    public void show(Group root) {
        theBuilding.show(root);
    }

    public Building getTheBuilding() {
        return theBuilding;
    }

    public void update(String kind, boolean roof, boolean windows, boolean door) {
        switch (kind) {
            case "House":
                theBuilding = new SmallHouse(roof, windows, door);
                break;
            case "Building":
                theBuilding = new TallBuilding(roof, windows, door);
                break;
            case "Castle":
                theBuilding = new Castle(roof, windows, door);
                break;
        }
    }

    public void setProperty(String property, boolean value) {
        theBuilding.setProperty(property, value);
    }

    public void changeRoofColor(String roofColor) {
        theBuilding.changeRoofColor(roofColor);
    }
}
