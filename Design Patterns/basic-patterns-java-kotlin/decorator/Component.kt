package decorator

import javafx.scene.shape.Circle

interface Component {
    fun operation()
    val circle: Circle
}