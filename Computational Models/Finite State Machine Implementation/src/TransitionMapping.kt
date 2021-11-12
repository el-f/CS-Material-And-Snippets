import java.io.PrintStream
import kotlin.Throws

abstract class TransitionMapping {
    abstract fun transitions(): Set<Transition>
    abstract fun prettyName(): String?
    fun prettyPrint(out: PrintStream) {
        out.print("{")
        val p = transitions().iterator()
        if (p.hasNext()) {
            p.next().prettyPrint(out)
        }
        while (p.hasNext()) {
            out.print(", ")
            p.next().prettyPrint(out)
        }
        out.print("}")
    }

    fun encode(): String {
        val encoding = StringBuilder()
        val transitionsList: MutableList<Transition> = transitions().toMutableList()
        transitionsList.sort()
        val p = transitionsList.iterator()
        if (p.hasNext()) {
            encoding.append(p.next().encode())
        }
        while (p.hasNext()) {
            encoding.append(";").append(p.next().encode())
        }
        return encoding.toString()
    }

    abstract fun at(state: State, symbol: Char): Set<State>

    /**
     * Checks that the transition mapping contains valid states and symbols.
     *
     * @param states   the states of the state machine that holds this mapping
     * @param alphabet the alphabet of the state machine that holds this mapping
     * @throws Exception if it finds a transition with a state that does not belong to the machine or a symbol that does not belong to the machine's alphabet.
     */
    @Throws(Exception::class)
    fun verify(states: Set<State?>, alphabet: Alphabet) {
        for (t in transitions()) {
            if (!states.contains(t.fromState())) {
                throw Exception("Transition mapping contains a state (id " + t.fromState() + ") that is not a part of the state machine.")
            }
            if (t.symbol() != Alphabet.EPSILON && !alphabet.contains(t.symbol())) {
                throw Exception("Transition contains symbol " + t.symbol() + " that is not a part of the machine's alphabet")
            }
            if (!states.contains(t.toState())) {
                throw Exception("Transition mapping contains a state (id " + t.toState() + ") that is not a part of the state machine.")
            }
        }
    }
}