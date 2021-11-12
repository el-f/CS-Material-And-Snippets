import java.io.PrintStream

class Transition(private val fromState: State, private val symbol: Char, private val toState: State) :
    Comparable<Transition> {
    fun fromState(): State {
        return fromState
    }

    fun symbol(): Char {
        return symbol
    }

    fun toState(): State {
        return toState
    }

    fun prettyPrint(out: PrintStream) {
        out.print("(")
        fromState.prettyPrint(out)
        out.print(", ")
        if (symbol == Alphabet.EPSILON) out.print("\u03B5") else out.print(symbol)
        out.print(", ")
        toState.prettyPrint(out)
        out.print(")")
    }

    fun encode(): String {
        return fromState.encode() + "," + (if (symbol == Alphabet.EPSILON) "" else symbol) + "," + toState.encode()
    }

    override fun compareTo(other: Transition): Int {
        var result = fromState.compareTo(other.fromState)
        if (result != 0) return result
        result = symbol.compareTo(other.symbol)
        return if (result != 0) result else toState.compareTo(other.toState)
    }
}