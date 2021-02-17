package memento.player

import java.lang.StringBuilder
import java.util.ArrayList
import java.util.function.Consumer

class CareTaker {
    private val list: MutableList<Memento>
    fun save(pm: Memento) {
        list.add(pm)
    }

    fun load(index: Int) {
        list[index].load()
    }

    override fun toString(): String {
        val sb = StringBuilder("Saves:\n")
        list.forEach(Consumer { pm: Memento? -> sb.append(pm).append("\n") })
        return sb.toString()
    }

    init {
        list = ArrayList()
    }
}