package tutorial._6_Inheritence

import tutorial._4_Classes.Person
import tutorial._5_Interfaces.BasicInfoProvider
import tutorial._5_Interfaces.PersonInfoProvider
import tutorial._5_Interfaces.checkTypes

class FancyInfoProvider : BasicInfoProvider() {
    override val providerInfo: String
        get() = "Fancy Info Provider"

    override fun printInfo(person: Person) {
        super.printInfo(person)
        println("Fancy Info")
    }

    override val sessionIDPreFix: String
        get() = "Fancy Session"
}


fun main() {
    val provider = FancyInfoProvider()
    provider.printInfo(Person())
    checkTypes(provider)

    /*
     *   Object Expression
     */
    val provider2 = object : PersonInfoProvider {
        override val providerInfo: String
            get() = "New Info Provider"

        fun getSessionID() = "ID"
    }
}
