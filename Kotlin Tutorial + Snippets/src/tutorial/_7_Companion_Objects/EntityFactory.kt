package tutorial._7_Companion_Objects

interface IDProvider {
    fun getID(): String
}

class Entity private constructor(val id: String) {

    companion object : IDProvider { //can also name it: companion object Factory {
        override fun getID(): String {
            return "123"
        }

        const val id = "ID"
        fun create() = Entity(id)
    }
}

fun main() {
    val entity = Entity.create()
    println(entity.id)
    println(Entity.id)
    println(Entity.getID())
}