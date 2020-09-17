package tutorial._5_Interfaces

import tutorial._4_Classes.Person

interface PersonInfoProvider {
    val providerInfo: String

    fun printInfo(person: Person) {
        println(providerInfo)
        println(person.getInfo())
    }
}

interface SessionInfoProvider {
    fun getSessionID()
}

//open keyword allows extending the class
open class BasicInfoProvider : PersonInfoProvider, SessionInfoProvider {
    override val providerInfo: String
        get() = "BasicInfoProvider"

    protected open val sessionIDPreFix = "Session" //open keywords allows override

    override fun printInfo(person: Person) {
        super.printInfo(person)
        println("override method")

    }

    override fun getSessionID() {
        println(sessionIDPreFix)
    }
}

fun main() {
    val provider = BasicInfoProvider()
    provider.printInfo(Person())
    provider.getSessionID()

    checkTypes(provider)
}

fun checkTypes(infoProvider: PersonInfoProvider) {
    if (infoProvider is SessionInfoProvider) {
        println("is a session info provider")
        (infoProvider as SessionInfoProvider).getSessionID()
        infoProvider.getSessionID() //smart cast
    } else {
        println("is not a session info provider")
        //infoProvider.getSessionID() // smart cast sees impossible cast
    }
}