package View;


import Model.Model;
import javafx.beans.value.ChangeListener;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.RadioButton;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.util.ArrayList;

public class View {
    private final ComboBox<String> roofColors;
    private final Group root;
    private final RadioButton rbHouse;
    private final RadioButton rbBuilding;
    private final RadioButton rbCastle;
    private final CheckBox cbRoof;
    private final CheckBox cbWindows;
    private final CheckBox cbDoor;
    private final ToggleGroup tg;
    private final Text txt;
    private final HBox hBox;
    private final ArrayList<Rectangle> windows;

    public View(Stage stage) {
        root = new Group();
        tg = new ToggleGroup();
        rbHouse = new RadioButton("House");
        rbHouse.setToggleGroup(tg);
        rbBuilding = new RadioButton("Building");
        rbBuilding.setToggleGroup(tg);
        rbBuilding.setSelected(true);
        rbCastle = new RadioButton("Castle");
        rbCastle.setToggleGroup(tg);
        cbDoor = new CheckBox("Door");
        cbRoof = new CheckBox("Roof");
        cbWindows = new CheckBox("Windows");
        windows = new ArrayList<>(); //add windows as controls
        VBox vbLeft = new VBox();
        vbLeft.getChildren().addAll(rbBuilding, rbCastle, rbHouse);
        vbLeft.setAlignment(Pos.CENTER_LEFT);
        VBox vbRight = new VBox();
        vbRight.setAlignment(Pos.CENTER_LEFT);
        vbRight.getChildren().addAll(cbDoor, cbRoof, cbWindows);

        VBox.setMargin(cbDoor, new Insets(5, 5, 5, 5));
        VBox.setMargin(cbRoof, new Insets(5, 5, 5, 5));
        VBox.setMargin(cbWindows, new Insets(5, 5, 5, 5));

        VBox.setMargin(rbHouse, new Insets(5, 5, 5, 5));
        VBox.setMargin(rbBuilding, new Insets(5, 5, 5, 5));
        VBox.setMargin(rbCastle, new Insets(5, 5, 5, 5));

        Pane drawPane = new Pane();
        drawPane.getChildren().add(root);

        roofColors = new ComboBox<>();
        roofColors.getItems().addAll("Red", "Green", "Grey");
        roofColors.setValue("Red");
        txt = new Text("Roof Colors: ");
        hBox = new HBox();
        hBox.setAlignment(Pos.CENTER);

        BorderPane bp = new BorderPane();
        bp.setLeft(vbLeft);
        bp.setRight(vbRight);
        bp.setCenter(root);
        bp.setBottom(hBox);

        Scene scene = new Scene(bp, 500, 500);
        stage.setScene(scene);
        stage.show();
    }

//    public void addEventMousePressedToScene(EventHandler<Event> mousePressedEvent) {
//    }

    public void update(Model model) {
        root.getChildren().clear();
        model.show(root);
        if (cbWindows.isSelected()){
            root.getChildren().addAll(windows);
        }
    }

    public boolean getRoofSelected() {
        return cbRoof.isSelected();
    }

    public boolean getDoorSelected() {
        return cbDoor.isSelected();
    }

    public boolean getWindowsSelected() {
        return cbWindows.isSelected();
    }


    public String getKind() {
        if (rbHouse.isSelected())
            return rbHouse.getText();
        else if (rbBuilding.isSelected())
            return rbBuilding.getText();
        else if (rbCastle.isSelected())
            return rbCastle.getText();
        else return null;
    }

    public String getRoofColor() {
        return roofColors.getValue();
    }

    public void addChangeListenerToToggleGroup(ChangeListener<javafx.scene.control.Toggle> changeListener) {
        tg.selectedToggleProperty().addListener(changeListener);
    }

    public void addChangeListenerToRoof(ChangeListener<Boolean> clRoof) {
        cbRoof.selectedProperty().addListener(clRoof);
    }

    public void addChangeListenerToWindows(ChangeListener<Boolean> clWindows) {
        cbWindows.selectedProperty().addListener(clWindows);
    }

    public void addChangeListenerToRoofColors(ChangeListener<String> cl) {
        roofColors.valueProperty().addListener(cl);
    }

    public void addChangeListenerToDoor(ChangeListener<Boolean> clDoor) {
        cbDoor.selectedProperty().addListener(clDoor);
    }

    public void addRoofColorsComboBox() {
        hBox.getChildren().addAll(txt, roofColors);
    }

    public void hideRoofColorsComboBox() {
        hBox.getChildren().clear();
    }

    public void addWindow(Rectangle window) {
        windows.add(window);
    }

    //when the windows checkbox is unchecked we don't need windows.
    public void removeWindows() {
        windows.clear();
    }

    public void changeWindowColor(Rectangle w) {
        int index = windows.indexOf(w);
        if (windows.get(index).getFill() != Color.BLACK)
            windows.get(index).setFill(Color.BLACK);
        else windows.get(index).setFill(Color.YELLOW);
    }

    public ArrayList<Rectangle> getWindows() {
        return windows;
    }
}
