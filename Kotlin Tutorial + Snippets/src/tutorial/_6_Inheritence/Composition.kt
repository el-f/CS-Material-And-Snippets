package tutorial._6_Inheritence

interface Swimming {
    fun swim()
}

class SwimmingImplementation : Swimming {
    override fun swim() {
        println("swim!")
    }
}

interface Jumping {
    fun jump()
}

class JumpingImplementation : Jumping {
    override fun jump() {
        println("jump!")
    }
}

class Frog(
    swimmingImplementation: Swimming = SwimmingImplementation(),
    jumpingImplementation: Jumping = JumpingImplementation()
) : Swimming by swimmingImplementation, Jumping by jumpingImplementation

fun main() {
    val frog = Frog()
    frog.jump() // jump!
    frog.swim() // swim!
}