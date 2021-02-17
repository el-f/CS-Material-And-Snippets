package decorator

import javafx.scene.shape.Circle

abstract class Decorator(private val component: Component) : Component {
    override fun operation() {
        component.operation()
    }

    override val circle: Circle
        get() = component.circle
}