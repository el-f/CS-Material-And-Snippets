package observer

class Student(private val name: String, private val grade: Int) : Observer {
    override fun toString(): String {
        return "$name, $grade"
    }

    override fun update() {
        println("Hi from student: $name")
    }
}