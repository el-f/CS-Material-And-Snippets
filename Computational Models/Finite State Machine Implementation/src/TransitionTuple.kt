import java.util.*
import kotlin.collections.HashSet


class TransitionTuple(private var fromStateId: Int, private var symbol: Char, private var toStateId: Int) {
    fun fromStateId(): Int {
        return fromStateId
    }

    fun symbol(): Char {
        return symbol
    }

    fun toStateId(): Int {
        return toStateId
    }

    companion object {
        private fun parseTuple(encoding: String): TransitionTuple {
            val scanner = Scanner(encoding)
            scanner.useDelimiter("\\s*,\\s*")
            val fromStateId = scanner.nextInt()
            val symbol: Char
            val symbolOrNothing = scanner.next()
            symbol = if (symbolOrNothing.isEmpty()) Alphabet.EPSILON else symbolOrNothing[0]
            val toStateId = scanner.nextInt()
            scanner.close()
            return TransitionTuple(fromStateId, symbol, toStateId)
        }

        @JvmStatic
        fun parseTupleList(encoding: String): Set<TransitionTuple> {
            val scanner = Scanner(encoding)
            scanner.useDelimiter("\\s*;\\s*")
            val tuples: MutableSet<TransitionTuple> = HashSet()
            while (scanner.hasNext()) {
                tuples.add(parseTuple(scanner.next()))
            }
            scanner.close()
            return tuples
        }
    }
}