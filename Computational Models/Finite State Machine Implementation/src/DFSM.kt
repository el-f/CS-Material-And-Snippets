import kotlin.collections.HashMap
import kotlin.collections.HashSet


open class DFSM : NDFSM {
    /**
     * Builds a DFSM from a string representation (encoding)
     *
     * @param encoding the string representation of a DFSM
     * @throws Exception if the encoding is incorrect or if it does not represent a deterministic machine
     */
    constructor(encoding: String?) : super(encoding) {
        transitionFunction().verifyTotal(states, alphabet)
        transitionFunction().verifyNoEpsilonTransitions()
    }

    /**
     * Build a DFSM from its components
     *
     * @param states          the set of states for this machine
     * @param alphabet        this machine's alphabet
     * @param transitions     the transition mapping of this machine
     * @param initialState    the initial state (must be a member of states)
     * @param acceptingStates the set of accepting states (must be a subset of states)
     * @throws Exception if the components do not represent a deterministic machine
     */
    constructor(
        states: Set<State>,
        alphabet: Alphabet?,
        transitions: Set<Transition>,
        initialState: State?,
        acceptingStates: Set<State>
    ) : super(states, alphabet, transitions, initialState, acceptingStates) {
        transitionFunction().verifyTotal(states, alphabet!!)
        transitionFunction().verifyNoEpsilonTransitions()
    }

    protected constructor() : super()

    override fun create(): NDFSM {
        return DFSM()
    }

    override fun createMapping(transitions: Set<Transition>): TransitionMapping {
        return TransitionFunction(transitions)
    }

    private fun transitionFunction(): TransitionFunction {
        return transitionMapping as TransitionFunction
    }

    /**
     * Returns a minimal version of this state machine
     *
     * @return a DFSM that recognizes the same language as this machine, but has a minimal number of states.
     */
    fun minimize(): DFSM {
        return (removeUnreachableStates() as DFSM).minimizeWithNoUnreachableStates()
    }

    private fun minimizeWithNoUnreachableStates(): DFSM {
        val equivalent = equivalentStates()
        val minimalTransitions: MutableSet<Transition> = HashSet()
        for (t in transitionMapping.transitions()) {
            minimalTransitions.add(Transition(equivalent[t.fromState()]!!, t.symbol(), equivalent[t.toState()]!!))
        }
        val minimalAccepting: MutableSet<State?> = HashSet()
        for (s in acceptingStates) {
            minimalAccepting.add(equivalent[s])
        }
        val aDFSM = DFSM()
        aDFSM.states = HashSet(equivalent.values)
        aDFSM.alphabet = alphabet
        aDFSM.transitionMapping = TransitionFunction(minimalTransitions)
        aDFSM.initialState = equivalent[initialState]
        aDFSM.acceptingStates = minimalAccepting
        return aDFSM
    }

    // returns a map that maps each state to a representative of their equivalence class.
    private fun equivalentStates(): Map<State?, State?> {
        var prevEcc: Map<State?, State?> = HashMap()
        var ecc: MutableMap<State?, State?> = HashMap()

        /*
            We will represent each equivalence classes with a representative member
            and use a dictionary to map each state to this representative.

            First we create two equivalence classes, put all the accepting states in the first
            and all the non-accepting states in the second.
        */
        if (acceptingStates.isNotEmpty()) {
            val rep = acceptingStates.iterator().next()
            for (state in acceptingStates) ecc[state] = rep
        }
        val nonAcceptingStates: MutableSet<State> = HashSet(states)
        nonAcceptingStates.removeAll(acceptingStates)
        if (nonAcceptingStates.isNotEmpty()) {
            val rep = nonAcceptingStates.iterator().next()
            for (state in nonAcceptingStates) ecc[state] = rep
        }

        /*
            The invariant for the following loop is:
		    1. for any s -> r association in ecc, s is equivalent to r in prevEcc,
		    2. for any input symbol c, the destination of the transition from s on c is equivalent (in prevEcc) to
		        the destination of the transition from r to c,
		    3. for any two values r1, r2 in ecc, they are not equivalent to each other in prevEcc,
		    4. all the equivalence classes in prevEcc have a representative in ecc.
        */
        while (prevEcc != ecc) {
            prevEcc = ecc
            ecc = HashMap()

            /*
                To establish the invariant we will set ecc with the associations of the form

                r -> r where r is a representative from prevEcc.

                This will initially satisfy the invariant because our action establishes
                condition (4) and conditions (1) and (2) and (3) are correct by induction
                from the validity of prevEcc."
            */
            for (state in prevEcc.values) {
                ecc[state] = state
            }
            for (state in states) {

                /*
                    For each state s, we look in ecc for a rep r that is equivalent to s in prevEcc
                    (that is, s's rep in prevEcc is r and for every input they transition to the same
                    equivalence class in prevEcc) and add s to ecc with the same equivalence rep.
                    If no state is equivalent to s, we add s to ecc as its own rep.
                 */
                val p: Iterator<State?> = ecc.keys.iterator()
                var rep: State? = null
                var equivalent = false
                while (p.hasNext() && !equivalent) {
                    rep = p.next()
                    equivalent = equivalentIn(prevEcc, state, rep)
                }
                if (equivalent) ecc[state] = rep else ecc[state] = state
            }
        }
        return ecc
    }

    private fun equivalentIn(equivRel: Map<State?, State?>, s: State, t: State?): Boolean {
        if (equivRel[s] !== equivRel[t]) return false
        var equiv = true
        val p: Iterator<Char> = alphabet.iterator()
        var symbol: Char
        while (p.hasNext() && equiv) {
            symbol = p.next()
            equiv = equivRel[transitionFunction().applyTo(s, symbol)] === equivRel[transitionFunction().applyTo(
                t!!, symbol
            )]
        }
        return equiv
    }

    /**
     * Returns true if and only if input belongs to this machine's language.
     *
     * @param input a string whose characters are members of this machine's alphabet
     * @return a boolean that indicates if the input is a member of this machine's language or not
     */
    override fun compute(input: String): Boolean {
        var state = initialState
        for (element in input) state = transitionFunction().applyTo(state, element)
        return acceptingStates.contains(state)
    }

    @Throws(Exception::class)
    fun complement(): DFSM {
        val nonAcceptingStates: MutableSet<State> = HashSet(states)
        nonAcceptingStates.removeAll(acceptingStates)
        return DFSM(states, alphabet, transitionMapping.transitions(), initialState, nonAcceptingStates)
    }
}