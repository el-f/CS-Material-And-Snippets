import java.io.PrintStream
import java.util.*
import kotlin.collections.HashSet

class IdentifiedState(private val id: Int) : State() {
    override val instanceID: Int = (Math.random() * 100).toInt()
    override fun prettyPrint(out: PrintStream) {
        out.print(id)
    }

    override fun toString(): String {
        return "id=$id"
    }

    override fun encode(): String {
        return "" + id
    }

    override fun hashCode(): Int {
        val prime = 31
        var result = 1
        result = prime * result + id.hashCode()
        return result
    }

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (other == null) return false
        if (javaClass != other.javaClass) return false
        return id == (other as IdentifiedState).id
    }

    override operator fun compareTo(other: State?): Int {
        return id.compareTo((other as IdentifiedState).id)
    }

    companion object {
        @JvmStatic
        fun parseStateIdList(encoding: String): Set<Int> {
            val scanner = Scanner(encoding)
            val ids: MutableSet<Int> = HashSet()
            while (scanner.hasNext()) {
                ids.add(scanner.nextInt())
            }
            scanner.close()
            return ids
        }
    }

}