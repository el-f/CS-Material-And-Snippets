package tutorial._8_Object_Declaration

import tutorial._8_Object_Declaration.EntityType.*
import java.util.*

enum class EntityType {
    EASY, MEDIUM, HARD;

    fun getFormattedName() = name.toLowerCase().capitalize()
}

object EntityFactory {
    //  fun create() = Entity2("id", "name")
    fun create(type: EntityType): Entity2 {
        val id = UUID.randomUUID().toString()
        val name = type.getFormattedName()
        return Entity2(id, name)
    }
}

class Entity2(private val id: String, private val name: String) {
    override fun toString(): String {
        return "ID: $id Name: $name"
    }
}

fun main() {
    val entity = EntityFactory.create(EASY)
    println(entity)

    val mediumEntity = EntityFactory.create(MEDIUM)
    println(mediumEntity)

    val hardEntity = EntityFactory.create(HARD)
    println(hardEntity)
}