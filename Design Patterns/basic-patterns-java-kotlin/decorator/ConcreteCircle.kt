package decorator

import javafx.scene.paint.Color
import javafx.scene.shape.Circle

class ConcreteCircle(radius: Double) : Circle(radius), Component {
    override fun operation() {
        fill = Color.TRANSPARENT
        stroke = Color.BLACK
    }

    override val circle: Circle
        get() = this
}