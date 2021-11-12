import java.io.PrintStream
import java.util.*
import kotlin.collections.ArrayList
import kotlin.collections.HashMap

/**
 * Creates a new alphabet from the given list of symbols.
 * We assume that the list does not contain duplicates.
 *
 *
 * For example, the statement
 *
 * `
 * Alphabet abc = new Alphabet(new ArrayList<Character>(Arrays.asList('a', 'b', 'c')));
` *
 *
 *
 * creates a new alphabet object that represents the alphabet {a,b,c} with the lexicographical
 * order given by a &lt; b &lt; c.
 *
 * @param: symbols a list of character symbols
 */
class Alphabet(private val symbols: MutableList<Char>) : Iterable<Char?> {
    private val succ: MutableMap<Char?, Char?>

    init {
        succ = HashMap()
        val p: Iterator<Char> = symbols.iterator()
        var current: Char? = null
        if (p.hasNext()) current = p.next()
        while (p.hasNext()) {
            succ[current] = p.next()
        }
    }

    /**
     * Prints the alphabet in set notation.
     *
     *
     * For example, the statements
     * `
     * Alphabet abc = new Alphabet(new ArrayList<Character>(Arrays.asList('a', 'b', 'c')));
     * abc.prettyPrint(System.out);
    ` *
     *
     * will print
     * `
     * {a, b, c}
    ` *
     *
     * on standard output.
     *
     * @param out the print stream on which to print this alphabet
     */
    fun prettyPrint(out: PrintStream) {
        out.print("{")
        val p: Iterator<Char> = symbols.iterator()
        if (p.hasNext()) {
            out.print(p.next())
        }
        while (p.hasNext()) {
            out.print(", ")
            out.print(p.next())
        }
        out.print("}")
    }

    /**
     * Returns a string encoding of this alphabet.
     *
     *
     *  The encoding is identical to the format that `Alphabet.parse`
     * accepts. In other words, encode() and parse() are inverses:
     * `
     * forall anAlphabet : Alphabet | Alphabet.parse(anAlphabet.encode()).equals(anAlphabet)
    ` *
     *
     * @return a string encoding of this alphabet
     */
    fun encode(): String {
        val encoding = StringBuilder()
        val p: Iterator<Char> = symbols.iterator()
        if (p.hasNext()) encoding.append(p.next())
        while (p.hasNext()) {
            encoding.append(" ").append(p.next())
        }
        return encoding.toString()
    }

    /*
     * (non-Javadoc)
     * @see java.lang.Iterable#iterator()
     */
    override fun iterator(): MutableIterator<Char> {
        return symbols.iterator()
    }

    /**
     * Returns true if and only if symbol is a member of this alphabet.
     *
     * @param symbol a character
     * @return true if and only if symbol is a member of this alphabet
     */
    operator fun contains(symbol: Char): Boolean {
        return symbols.contains(symbol)
    }

    /**
     * Returns the first string in the lexicographical order of this alphabet (it's always the empty string).
     *
     * @return the empty string
     */
    fun first(): String {
        return ""
    }

    /**
     * Given a string from this alphabet, returns the next string in this alphabet's lexicographical order.
     *
     *
     * For example, if alphabet is the alphabet {a,b,c} then
     * `
     * alphabet.next("abc")
    ` *
     *
     * returns the string `"aca"`.
     *
     * @param string a string whose characters are members of this alphabet
     * @return the next string in this alphabet's lexicographical order
     */
    fun next(string: String): String {
        val nextString = StringBuilder()
        var i = string.length - 1

        // abb      baa
        while (i >= 0 && succ[string[i]] == null) {
            nextString.append(symbols[0])
            --i
        }
        if (i >= 0) {
            nextString.append(succ[string[i]])
            i--
            while (i >= 0) {
                nextString.append(string[i])
                i--
            }
        } else nextString.append(symbols[0])
        return StringBuffer(nextString.toString()).reverse().toString()
    }

    fun getSymbols(): List<Char> {
        return symbols
    }

    companion object {
        /**
         * Represents the empty string.
         *
         *
         * This symbol is used to represent epsilon transitions.
         */
        const val EPSILON = '\u0000'

        /**
         * Creates a new alphabet from the string encoding of an alphabet.
         *
         *
         * The format of the encoding is
         *
         * <pre> &lt;char&gt; &lt;char&gt; ...  </pre>
         *
         *
         * That is, the symbols are characters, separated by whitespace. The lexicographical order of
         * the alphabet follows the order of the list. We assume that the list does not contain duplicates.
         * For example, the statement
         *
         * `
         * Alphabet abc = Alphabet.parse('a b c');
        ` *
         *
         *
         * creates the alphabet <pre>{a,b,c}</pre> with the lexicographical order given by <pre>a &lt; b &lt; c.</pre>
         *
         * @param encoding a string encoding of an alphabet
         * @return the alphabet object representing the encoded alphabet
         */
        @JvmStatic
        fun parse(encoding: String): Alphabet {
            val scanner = Scanner(encoding)
            val symbols: MutableList<Char> = ArrayList()
            while (scanner.hasNext()) {
                symbols.add(scanner.next()[0])
            }
            scanner.close()
            return Alphabet(symbols)
        }
    }
}