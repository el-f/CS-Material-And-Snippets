package observer

import java.util.HashSet

class MyButton {
    private val set: MutableSet<Observer> = HashSet()
    fun attach(o: Observer) {
        set.add(o)
    }

    fun push() {
        notify_button()
    }

    private fun notify_button() {
        for (o in set) o.update()
    }
}