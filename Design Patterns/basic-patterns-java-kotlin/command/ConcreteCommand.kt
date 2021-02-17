package command

import javafx.scene.paint.Color
import javafx.scene.shape.Circle

class ConcreteCommand(private val circle: Circle) : Command {
    private var previousColor: Color? = null
    override fun execute() {
        previousColor = circle.fill as Color
        circle.fill = Color.color(Math.random(), Math.random(), Math.random())
    }

    override fun undo() {
        circle.fill = previousColor
    }
}