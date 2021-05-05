package tutorial._9_Sealed_and_Data_Classes_and_Extensions

import tutorial._9_Sealed_and_Data_Classes_and_Extensions.EntityType2.*
import java.util.*

enum class EntityType2 {
    EASY, MEDIUM, HARD, HELP;

    fun getFormattedName() = name.lowercase().replaceFirstChar { it.titlecase() }
}

object EntityFactory2 {
    //  fun create() = Entity2("id", "name")
    fun create(type: EntityType2): Entity2 {
        val id = UUID.randomUUID().toString()
        val name = type.getFormattedName()
        return when (type) {
            EASY -> Entity2.Easy(id, name)
            MEDIUM -> Entity2.Medium(id, name)
            HARD -> Entity2.Hard(id, name, 2f)
            HELP -> Entity2.Help
        }
    }
}

sealed class Entity2 {
    object Help : Entity2() {
        const val name = "Help"
    }

    data class Easy(private val id: String, private val name: String) : Entity2() {
//        override fun equals(other: Any?): Boolean {
//            return super.equals(other)
//        }
//
//        override fun hashCode(): Int {
//            return super.hashCode()
//        }
    }

    data class Medium(val id: String, private val name: String) : Entity2()
    data class Hard(private val id: String, private val name: String, val multiplier: Float) : Entity2()
}

fun Entity2.Medium.printInfo() {
    println("Medium class: $id")
}

val Entity2.Medium.info: String
    get() = "some info"

fun main() {
//    Entity2.Medium("id","name").printInfo()       //"static"
    val e = Entity2.Medium("id", "name")
    e.printInfo()
    println(e.info)
    val eFromFactory = EntityFactory2.create(MEDIUM)
//    eFromFactory.printInfo()  //compiler doesnt recognize the additional function
//    eFromFactory.info         // /
    if (eFromFactory is Entity2.Medium) {
        eFromFactory.printInfo()
        println(eFromFactory.info)
    }

    val msg = when (EntityFactory2.create(EASY)) {
        Entity2.Help -> "help class"
        is Entity2.Easy -> "easy class"
        is Entity2.Medium -> "medium class"
        is Entity2.Hard -> "hard class"
    }
    println(msg)

    //class equals are comparing reference
    val ent1 = EntityFactory2.create(EASY)
    val ent2 = EntityFactory2.create(EASY)
    println(ent1 == ent2)

    //data class equals even with different reference
    val e1 = Entity2.Easy("id", "name")
    val e2 = Entity2.Easy("id", "name")
    val e3 = e1.copy()
    val e4 = e1.copy(name = "new name")
    println(e1 == e2)
    println(e1 == e3)
    println(e1 == e4)

    //equals with reference
    println(e1 === e2)
}