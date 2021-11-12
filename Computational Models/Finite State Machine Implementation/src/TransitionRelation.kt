class TransitionRelation(transitions: Set<Transition>) : TransitionMapping() {
    private val transitions: MutableMap<State, MutableSet<Transition>>

    init {
        this.transitions = HashMap()
        for (t in transitions) {
            if (!this.transitions.containsKey(t.fromState())) this.transitions[t.fromState()] = HashSet()
            this.transitions[t.fromState()]!!.add(t)
        }
    }

    override fun transitions(): Set<Transition> {
        val result: MutableSet<Transition> = HashSet()
        for (s in transitions.values) result.addAll(s)
        return result
    }

    override fun prettyName(): String {
        return "\u0394"
    }

    override fun at(state: State, symbol: Char): Set<State> {
        val result: MutableSet<State> = HashSet()
        if (!transitions.containsKey(state)) return result
        for (t in transitions[state]!!) if (Character.valueOf(t.symbol()) == symbol) result.add(t.toState())
        return result
    }


}