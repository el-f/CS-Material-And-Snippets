package structures.hash_tables

import java.util.*

// Java code illustrating clear() and clone() methods
//@SuppressWarnings("unchecked")
fun main() {
    // creating a hash table
    val h = Hashtable<Int, String>()
    val h1: Hashtable<*, *>
    h[3] = "Geeks"
    h[2] = "forGeeks"
    h[1] = "isBest"

    // create a clone or shallow copy of hash table h
    h1 = h.clone() as Hashtable<*, *>

    // checking clone h1
    println("values in clone: $h1")

    // clear hash table h
    h.clear()

    // checking hash table h
    println("after clearing: $h")
}