package adapter

class IPhoneX : IPhone {
    override val name: String
        get() = "IPhone X"

    override fun chargeIPhone() {
        println("$name is charging...")
    }
}