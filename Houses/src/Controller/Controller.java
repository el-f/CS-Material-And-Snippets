package Controller;

import Model.Model;
import View.View;
import javafx.beans.value.ChangeListener;
import javafx.scene.control.Toggle;
import javafx.scene.input.MouseEvent;
import javafx.scene.shape.Rectangle;


public class Controller {
    private final Model model;
    private final View view;

    public Controller(Model m, View v) {
        model = m;
        view = v;
        view.update(model);

        ChangeListener<Toggle> changeListener = (observable, oldValue, newValue) -> {
            String kind = view.getKind();
            model.update(kind, view.getRoofSelected(), view.getWindowsSelected(), view.getDoorSelected());
            view.getWindows().clear();
            addWindowsToView();
            model.changeRoofColor(view.getRoofColor());
            view.update(model);
        };

        view.addChangeListenerToToggleGroup(changeListener);

        ChangeListener<Boolean> clRoof = (observable, oldValue, newValue) -> {
            if (view.getRoofSelected())
                view.addRoofColorsComboBox();
            else
                view.hideRoofColorsComboBox();
            model.setProperty("roof", view.getRoofSelected());
            view.update(model);
        };
        view.addChangeListenerToRoof(clRoof);

        ChangeListener<Boolean> clWindows = (observable, oldValue, newValue) -> {
            boolean isSelected = view.getWindowsSelected();
            model.setProperty("windows", isSelected);
            if (isSelected) {    //add windows to view
                addWindowsToView();
            } else {             //remove windows to view
                view.removeWindows();
            }
            view.update(model);
        };
        view.addChangeListenerToWindows(clWindows);

        ChangeListener<Boolean> clDoor = (observable, oldValue, newValue) -> {
            model.setProperty("door", view.getDoorSelected());
            view.update(model);
        };
        view.addChangeListenerToDoor(clDoor);

        ChangeListener<String> clRoofColors = (observable, oldValue, newValue) -> {
            model.changeRoofColor(view.getRoofColor());
            view.update(model);
        };
        view.addChangeListenerToRoofColors(clRoofColors);
    }

    public void addWindowsToView(){
        model.getTheBuilding().getWindows().forEach(w -> {
            Rectangle tmpWindow = new Rectangle(w.getX(), w.getY(), w.getWidth(), w.getHeight());
            tmpWindow.addEventHandler(MouseEvent.MOUSE_CLICKED, event -> {
//                event.getTarget();
                view.changeWindowColor(tmpWindow);
            });
            view.addWindow(tmpWindow);
        });
    }

}
