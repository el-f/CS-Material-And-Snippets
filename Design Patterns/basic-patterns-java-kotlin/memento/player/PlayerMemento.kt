package memento.player

import java.time.LocalDate

class PlayerMemento(private val player: Player) : Memento {
    val name: String = player.name
    private val point: Int = player.point
    private val level: Int = player.level
    private val created: LocalDate = LocalDate.now()

    override fun toString(): String {
        return "$name $created"
    }

    override fun load() {
        player.level = level
        player.name = name
        player.point = point
    }

}