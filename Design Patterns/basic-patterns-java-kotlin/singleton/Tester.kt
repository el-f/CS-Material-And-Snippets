package singleton


fun main() {
    val idGen = IdGenerator.getInstance(0)
    println("IDGen Next Id: " + idGen.next)
    println("IDGen Next Id: " + idGen.next)
    val idGen2 = IdGenerator.getInstance(1)
    println("IDGen2 Next Id: " + idGen2.next)
    println("IDGen2 Next Id: " + idGen2.next)
    val idGen3 = IdGenerator.getInstance(0)
    println("IDGen3 Next Id: " + idGen3.next)
    println("IDGen3 Next Id: " + idGen3.next)
}