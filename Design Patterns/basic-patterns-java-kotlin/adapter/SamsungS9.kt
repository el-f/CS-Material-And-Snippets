package adapter

class SamsungS9 : Samsung {
    override val name: String
        get() = "Samsung S9"

    override fun chargeSamsung() {
        println("$name is charging...")
    }
}