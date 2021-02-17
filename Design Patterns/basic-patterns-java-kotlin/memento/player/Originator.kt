package memento.player

interface Originator {
    fun save(): Memento?
}