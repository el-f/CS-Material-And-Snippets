package structures.hash_tables

import java.util.*

fun main() {
    val hashMap: MutableMap<String, Int> = HashMap()
    hashMap["Smith"] = 31
    hashMap["Smith"] = 30
    hashMap["Anderson"] = 31
    hashMap["Lewis"] = 29
    hashMap["Cook"] = 29
    println("Display entries in HashMap")
    println(hashMap)

    // Create a TreeMap from the previous HashMap
    val treeMap: Map<String, Int> = TreeMap(hashMap)
    println("\nDisplay entries in ascending order of key")
    println(treeMap)

    // Create a LinkedHashMap
    val linkedHashMap1: MutableMap<String, Int> = LinkedHashMap()
    // 16 - capacity, 0.75f - loading factor, true - retrieve as the
    // hashing access, false - retrieve as the insertion order
    val linkedHashMap2: MutableMap<String, Int> = LinkedHashMap(16, 0.75f, true)
    linkedHashMap1["Smith"] = 30
    linkedHashMap2["Smith"] = 30
    linkedHashMap1["Anderson"] = 31
    linkedHashMap2["Anderson"] = 31
    linkedHashMap1["Lewis"] = 29
    linkedHashMap2["Lewis"] = 29
    linkedHashMap1["Cook"] = 29
    linkedHashMap2["Cook"] = 29
    // Display the age for Lewis
    println("The age for " + "Lewis is " + linkedHashMap1["Lewis"])

    println("\nDisplay entries in LinkedHashMap1")
    println(linkedHashMap1)
    println("\nDisplay entries in LinkedHashMap2")
    println(linkedHashMap2)

    linkedHashMap2["Anderson"]
    println("\nDisplay entries in LinkedHashMap2")
    println(linkedHashMap2)
}