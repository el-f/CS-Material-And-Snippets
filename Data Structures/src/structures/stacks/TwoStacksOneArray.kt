package structures.stacks

class TwoStacksOneArray internal constructor(totalSize: Int) {
    val isFull: Boolean
        get() = size1 + size2 == arr.size
    val isAllEmpty: Boolean
        get() = size1 == 0 && size2 == 0
    val isStackOneEmpty: Boolean
        get() = size1 == 0
    val isStackTwoEmpty: Boolean
        get() = size2 == 0

    fun push(firstStack: Boolean, num: Int): Boolean {
        if (isFull) return false
        if (firstStack) arr[size1++] = num else arr[arr.size - size2++ - 1] = num
        return true
    }

    @Throws(Exception::class)
    fun pop(firstStack: Boolean): Int {
        return getNumFromStack(firstStack, true)
    }

    @Throws(Exception::class)
    fun top(firstStack: Boolean): Int {
        return getNumFromStack(firstStack, false)
    }

    @Throws(Exception::class)
    fun getNumFromStack(firstStack: Boolean, pop: Boolean): Int {
        return if (firstStack && !isAllEmpty) {
            if (pop) arr[--size1] else arr[size1 - 1]
        } else if (!isAllEmpty) {
            if (pop) arr[arr.size - --size2 - 1] else arr[arr.size - size2]
        } else throw Exception()
    }

    companion object {
        lateinit var arr: IntArray
        var size1 = 0
        var size2 = 0

        @Throws(Exception::class)
        @JvmStatic
        fun main(args: Array<String>) {
            val twoSt = TwoStacksOneArray(100)
            //firstStack
            twoSt.push(true, 5)
            twoSt.push(true, -1)
            twoSt.push(true, 29)
            twoSt.push(true, 38)
            //secondStack
            twoSt.push(false, 99)
            twoSt.push(false, 123)
            twoSt.push(false, 251)

            //top
            println(twoSt.top(true))
            println(twoSt.top(false))
            //pop
            println(twoSt.pop(true))
            println(twoSt.pop(true))
            println(twoSt.pop(false))
            println(twoSt.pop(true))
            println(twoSt.pop(false))
            println(twoSt.pop(false))
            println(twoSt.pop(true))
        }
    }

    init {
        arr = IntArray(totalSize)
    }
}