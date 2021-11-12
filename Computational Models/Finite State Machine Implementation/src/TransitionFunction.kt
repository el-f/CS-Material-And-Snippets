import kotlin.Throws

class TransitionFunction(transitions: Set<Transition>) : TransitionMapping() {
    private val delta: Map<State, MutableMap<Char, State>>

    init {
        val delta: MutableMap<State, MutableMap<Char, State>> = HashMap()
        for (t in transitions) {
            if (!delta.containsKey(t.fromState())) delta[t.fromState()] = HashMap()
            delta[t.fromState()]!![t.symbol()] = t.toState()
        }
        this.delta = delta
    }


    fun applyTo(fromState: State, symbol: Char): State? {
        return delta[fromState]!![symbol]
    }

    private fun maps(fromState: State, symbol: Char): Boolean {
        return delta.containsKey(fromState) && delta[fromState]!!.containsKey(symbol)
    }

    override fun transitions(): Set<Transition> {
        val transitions: MutableSet<Transition> = HashSet()
        for ((key, value) in delta) {
            for ((key1, value1) in value) {
                transitions.add(Transition(key, key1, value1))
            }
        }
        return transitions
    }

    override fun prettyName(): String {
        return "\u03B4"
    }

    override fun at(state: State, symbol: Char): Set<State> {
        val result: MutableSet<State> = HashSet()
        if (symbol == Alphabet.EPSILON) return result
        result.add(applyTo(state, symbol)!!)
        return result
    }

    /**
     * Checks that the transition function is total.
     *
     * @param states   all the states of the DFSM
     * @param alphabet the alphabet of the DFSM
     * @throws Exception if there is a state that does not have a transition on all the symbols in the machine's alphabet.
     */
    @Throws(Exception::class)
    fun verifyTotal(states: Set<State>, alphabet: Alphabet) {
        for (symbol in alphabet) {
            for (state in states) {
                if (!maps(
                        state,
                        symbol
                    )
                ) throw Exception("The transition function is missing a transition from state $state on symbol $symbol")
            }
        }
    }

    /**
     * Checks that the transition function has no epsilon transitions.
     *
     * @throws Exception if there is an epsilon transition in the function
     */
    @Throws(Exception::class)
    fun verifyNoEpsilonTransitions() {
        for (m in delta.values) {
            if (m.containsKey(Alphabet.EPSILON)) throw Exception("The transition function has an epsilon transition")
        }
    }


}