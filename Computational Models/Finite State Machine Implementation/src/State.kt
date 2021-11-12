import java.io.PrintStream

abstract class State : Comparable<State?> {
    abstract fun prettyPrint(out: PrintStream)
    abstract override fun toString(): String
    abstract fun encode(): String
    abstract val instanceID: Int

    companion object {
        @JvmStatic
        fun prettyPrintStateSet(states: Collection<State>, out: PrintStream) {
            out.print("{")
            val p = states.iterator()
            if (p.hasNext()) {
                p.next().prettyPrint(out)
            }
            while (p.hasNext()) {
                out.print(", ")
                p.next().prettyPrint(out)
            }
            out.print("}")
        }

        @JvmStatic
        fun encodeStateSet(states: Set<State>): String {
            val encoding = StringBuilder()
            val statesList: MutableList<State> = states.toMutableList()
            statesList.sort()
            val p = statesList.iterator()
            if (p.hasNext()) {
                encoding.append(p.next().encode())
            }
            while (p.hasNext()) {
                encoding.append(" ").append(p.next().encode())
            }
            return encoding.toString()
        }
    }
}