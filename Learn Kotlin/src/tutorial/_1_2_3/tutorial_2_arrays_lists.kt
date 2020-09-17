package tutorial._1_2_3

fun sayHello(greeting: String, itemToGreet: String) {
    val msg = "$greeting $itemToGreet"
    println(msg)
}

fun main() {
    val things = arrayOf("kotlin", "programming", "books")
    sayHello("hello", "idiot")
    println(things.size)
    println(things[0])




    for (thing in things)
        println(thing)

    things.forEach { x -> print("$x ") }
    things.forEach { print("$it ") }
    print("\n")
    things.forEachIndexed { index, s ->
        println("$s is at $index")
    }
    val thingsList = listOf("kotlin", "programming", "books")
    val mutableThingsList = mutableListOf("kotlin", "programming", "books")
    mutableThingsList.add("wow")
    val map = mapOf(1 to "a", 2 to "b", 3 to "c")
    val mutableMap = mutableMapOf(1 to "a", 2 to "b", 3 to "c")
    mutableMap[4] = "d" // <=> mutableMap.put(4, "d")
    map.forEach { (key, value) -> println("$key -> $value") }
}