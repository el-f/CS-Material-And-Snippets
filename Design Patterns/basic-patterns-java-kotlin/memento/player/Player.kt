package memento.player

class Player(var name: String) : Originator {
    var point = 0
    var level = 1
    override fun toString(): String {
        return "Player [name=$name, point=$point, level=$level]"
    }

    override fun save(): Memento {
        return PlayerMemento(this)
    }
}