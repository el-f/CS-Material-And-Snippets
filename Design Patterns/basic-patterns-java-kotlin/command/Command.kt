package command

interface Command {
    fun execute()
    fun undo()
}