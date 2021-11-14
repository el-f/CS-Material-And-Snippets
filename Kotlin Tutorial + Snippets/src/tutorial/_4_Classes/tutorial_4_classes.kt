package tutorial._4_Classes

class Example(_num: Int) {
    val num = _num
}

class ExampleWithDefaults(val _num: Int = 3)

fun main() {
    val example = Example(5)
    println(example.num)

    val person = Person("john", "smith")
    println(person.firstName)
    println(person.lastName)

    val spiderMan = Person()        //default constructor defined in class
    println(spiderMan.firstName)
    println(spiderMan.lastName)

    val exampleWithDefaults = ExampleWithDefaults()
    println(exampleWithDefaults._num)

    spiderMan.nickName = "SPIDER-MAN"
    println(spiderMan.nickName)

    println(spiderMan.getInfo())
}