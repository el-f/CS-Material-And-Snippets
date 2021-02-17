package observer

class Lecturer(private val name: String) : Observer {
    override fun toString(): String {
        return name
    }

    override fun update() {
        println("Hello from lecturer: $name")
    }
}