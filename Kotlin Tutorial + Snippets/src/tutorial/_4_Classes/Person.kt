package tutorial._4_Classes

class Person(val firstName: String, val lastName: String) {

    constructor() : this("Peter", "Parker")

    var nickName: String? = null
        set(value) {
            field = value
            println("The new nickname is $value")
        }
        get() {
            println("The returned value is $field")
            return field
        }

    fun getInfo(): String {
        val nick = nickName ?: "no nickname"    //if (nickName != null) nickName else "no nickname"
        return "$firstName ($nick) $lastName"
    }
}

