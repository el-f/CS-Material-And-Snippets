package observer


// Observer design pattern with different objects

fun main() {
    val button = MyButton()
    button.attach(Student("Bamba", 89))
    button.attach(Student("Kinder Bueno", 55))
    button.attach(Lecturer("Bisli"))
    button.push()
}