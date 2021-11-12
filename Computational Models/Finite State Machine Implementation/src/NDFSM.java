import java.io.PrintStream;
import java.util.*;

public class NDFSM {

    protected TransitionMapping transitionMapping;
    protected Set<State> states;
    protected Set<State> acceptingStates;
    protected State initialState;
    protected Alphabet alphabet;

    /**
     * Builds a NDFSM from a string representation (encoding)
     *
     * @param encoding the string representation of a NDFSM
     * @throws Exception if the encoding is incorrect or if the transitions contain
     *                   invalid states or symbols
     */
    public NDFSM(String encoding) throws Exception {
        parse(encoding);

        transitionMapping.verify(states, alphabet);
    }

    /**
     * Build a NDFSM from its components
     *
     * @param states          the set of states for this machine
     * @param alphabet        this machine's alphabet
     * @param transitions     the transition mapping of this machine
     * @param initialState    the initial state (must be a member of states)
     * @param acceptingStates the set of accepting states (must be a subset of
     *                        states)
     * @throws Exception if the components do not represent a valid non
     *                   deterministic machine
     */
    public NDFSM(Set<State> states, Alphabet alphabet, Set<Transition> transitions, State initialState,
    Set<State> acceptingStates) throws Exception {

        initializeFrom(states, alphabet, transitions, initialState, acceptingStates);
        this.transitionMapping.verify(this.states, alphabet);
    }

    protected void initializeFrom(Set<State> states, Alphabet alphabet, Set<Transition> transitions, State initialState,
    Set<State> acceptingStates) {

        this.states = states;
        this.alphabet = alphabet;
        this.transitionMapping = createMapping(transitions);
        this.initialState = initialState;
        this.acceptingStates = acceptingStates;
    }

    protected NDFSM() {
    }

    /**
     * Overrides this machine with the machine encoded in string.
     *
     * <p>
     * Here's an example of the encoding:
     * </p>
     *
     * <pre>
    0 1/a b/0 , a , 0; 0,b, 1 ;1, a, 0 ; 1, b, 1/0/ 1
     * </pre>
     * <p>
     * This is the encoding of a finite state machine with two states (identified as
     * 0 and 1), an alphabet that consists of the two characters 'a' and 'b', and
     * four transitions:
     * </p>
     * <ol>
     * <li>From state 0 on character a it moves to state 0</li>
     * <li>from state 0 on character b it moves to state 1,</li>
     * <li>from state 1 on character a it moves to state 0,</li>
     * <li>from state 1 on character b it moves to state 1.</li>
     * </ol>
     * <p>
     * The initial state of this machine is 0, and the set of accepting states
     * consists of just one state 1. Here is the format in general:
     * </p>
     *
     * <pre>
    {@code
    <states> / <alphabet> / <transitions> / <initial state> / <accepting states>
    }
     * </pre>
     *
     * where:
     *
     * <pre>
    {@code
    <alphabet> is <char> <char> ...

    <transitions> is <transition> ; <transition> ...

    <transition> is from , char, to

    <initial state> is an integer

    <accepting states> is <state> <state> ...

    <state> is an integer
    }
     * </pre>
     *
     * @param string the string encoding
     * @throws Exception if the string encoding is invalid
     */
    public void parse(String string) throws Exception {

        Scanner scanner = new Scanner(string);

        scanner.useDelimiter("\\s*/");

        Map<Integer, State> states = new HashMap<>();

        for (Integer stateId : IdentifiedState.parseStateIdList(scanner.next())) {
            states.put(stateId, new IdentifiedState(stateId));
        }

        Alphabet alphabet = Alphabet.parse(scanner.next());

        Set<Transition> transitions = new HashSet<>();

        for (TransitionTuple t : TransitionTuple.parseTupleList(scanner.next())) {
            transitions.add(new Transition(states.get(t.fromStateId()), t.symbol(), states.get(t.toStateId())));
        }

        State initialState = states.get(scanner.nextInt());

        Set<State> acceptingStates = new HashSet<>();

        if (scanner.hasNext())
            for (Integer stateId : IdentifiedState.parseStateIdList(scanner.next())) {
            acceptingStates.add(states.get(stateId));
        }

        scanner.close();

        initializeFrom(new HashSet<>(states.values()), alphabet, transitions, initialState, acceptingStates);
        this.transitionMapping.verify(this.states, alphabet);
    }

    protected TransitionMapping createMapping(Set<Transition> transitions) {
        return new TransitionRelation(transitions);
    }

    /**
     * Returns a version of this state machine with all the unreachable states
     * removed.
     *
     * @return NDFSM that recognizes the same language as this machine, but has no
     *         unreachable states.
     */
    public NDFSM removeUnreachableStates() {

        Set<State> reachableStates = reachableStates();

        Set<Transition> transitionsToReachableStates = new HashSet<>();

        for (Transition t : transitionMapping.transitions()) {
            if (reachableStates.contains(t.fromState()) && reachableStates.contains(t.toState()))
                transitionsToReachableStates.add(t);
        }

        Set<State> reachableAcceptingStates = new HashSet<>();
        for (State s : acceptingStates) {
            if (reachableStates.contains(s))
                reachableAcceptingStates.add(s);
        }

        NDFSM aNDFSM = create();

        aNDFSM.initializeFrom(reachableStates, alphabet, transitionsToReachableStates, initialState,
            reachableAcceptingStates);

        return aNDFSM;
    }

    protected NDFSM create() {
        return new NDFSM();
    }

    // returns a set of all states that are reachable from the initial state

    private Set<State> reachableStates() {

        List<Character> symbols = new ArrayList<>();

        symbols.add(Alphabet.EPSILON);

        for (Character c : alphabet) {
            symbols.add(c);
        }

        Alphabet alphabetWithEpsilon = new Alphabet(symbols);

        Set<State> reachable = new HashSet<>();

        Set<State> newlyReachable = new HashSet<>();

        newlyReachable.add(initialState);

        while (!newlyReachable.isEmpty()) {
            reachable.addAll(newlyReachable);
            newlyReachable = new HashSet<>();
            for (State state : reachable) {
                for (Character symbol : alphabetWithEpsilon) {
                for (State s : transitionMapping.at(state, symbol)) {
                if (!reachable.contains(s))
                    newlyReachable.add(s);
            }
            }
            }
        }

        return reachable;
    }

    /**
     * Encodes this state machine as a string
     *
     * @return the string encoding of this state machine
     */
    public String encode() {
        return State.encodeStateSet(states) + "/" + alphabet.encode() + "/" + transitionMapping.encode() + "/"
        + initialState.encode() + "/" + State.encodeStateSet(acceptingStates);
    }

    /**
     * Prints a set notation description of this machine.
     *
     * <p>
     * To see the Greek symbols on the console in Eclipse, go to Window -&gt;
     * Preferences -&gt; General -&gt; Workspace and change
     * <tt>Text file encoding</tt> to <tt>UTF-8</tt>.
     * </p>
     *
     * @param out the output stream on which the description is printed.
     */
    public void prettyPrint(PrintStream out) {
        out.print("K = ");
        State.prettyPrintStateSet(states, out);
        out.println();

        out.print("\u03A3 = ");
        alphabet.prettyPrint(out);
        out.println();

        out.print(transitionMapping.prettyName() + " = ");
        transitionMapping.prettyPrint(out);
        out.println();

        out.print("s = ");
        initialState.prettyPrint(out);
        out.println();

        out.print("A = ");
        State.prettyPrintStateSet(acceptingStates, out);
        out.println();
    }

    /**
     * Returns a canonic version of this machine.
     *
     * <p>
     * The canonic encoding of two minimal state machines that recognize the same
     * language is identical.
     * </p>
     *
     * @return a canonic version of this machine.
     */

    public NDFSM toCanonicForm() {
        Set<Character> alphabetAndEpsilon = new HashSet<>();
        for (Character c : alphabet) {
            alphabetAndEpsilon.add(c);
        }
        alphabetAndEpsilon.add(Alphabet.EPSILON);

        Set<Transition> canonicTransitions = new HashSet<>();
        Stack<State> todo = new Stack<>();
        Map<State, State> canonicStates = new HashMap<>();
        int free = 0;

        todo.push(initialState);
        canonicStates.put(initialState, new IdentifiedState(free));
        free++;

        while (!todo.isEmpty()) {
            State top = todo.pop();
            for (Character symbol : alphabetAndEpsilon) {
                for (State nextState : transitionMapping.at(top, symbol)) {
                if (!canonicStates.containsKey(nextState)) {
                    canonicStates.put(nextState, new IdentifiedState(free));
                    todo.push(nextState);
                    free++;
                }
                canonicTransitions
                    .add(new Transition(canonicStates.get(top), symbol, canonicStates.get(nextState)));
            }
            }
        }

        Set<State> canonicAcceptingStates = new HashSet<>();
        for (State s : acceptingStates) {
            if (canonicStates.containsKey(s)) // unreachable accepting states will not appear in the canonic form of the
            // state machine
                canonicAcceptingStates.add(canonicStates.get(s));
        }

        NDFSM aNDFSM = create();

        aNDFSM.initializeFrom(new HashSet<>(canonicStates.values()), alphabet, canonicTransitions,
            canonicStates.get(initialState), canonicAcceptingStates);

        return aNDFSM;
    }

    public boolean compute(String input) {
        return toDFSM().compute(input);
    }

    public Set<State> eps(State state) {
        // get all epsilon transition states
        Set<State> eps = new HashSet<>(transitionMapping.at(state, Alphabet.EPSILON));

        // if no new states return only this one
        if (eps.isEmpty()) {
            eps.add(state);
            return eps;
        }

        // go over all new states and get all epsilon transitions
        List<State> newStates = new ArrayList<>();
        newStates.add(state);
        State current, last = null;
        while (!newStates.isEmpty()) {
            if (last != null && last.equals(newStates.get(0)))
                break; // empty language case

            current = newStates.get(0);
            newStates.addAll(transitionMapping.at(current, Alphabet.EPSILON));
            newStates.stream().filter(st -> !eps.contains(st)).forEach(eps::add);
            last = newStates.get(0);
            newStates.remove(0);
        }
        return eps;
    }

    public DFSM toDFSM() {
        int counter = 1;
        boolean isAccepting = false;
        Set<State> initialStates = eps(initialState);
        Set<State> newAcceptingStates = new HashSet<>();
        Queue<Set<State>> statesQueue = new LinkedList<>();
        Set<Transition> newTransitions = new HashSet<>();
        Map<Set<State>, IdentifiedState> map = new HashMap<>();
        statesQueue.add(initialStates);

        map.put(initialStates, new IdentifiedState(0));
        while (!statesQueue.isEmpty()) {
            Set<State> newStates;
            for (char c : alphabet) {
                newStates = new HashSet<>();
                for (State s : Objects.requireNonNull(statesQueue.peek())) {
                if ((!isAccepting) && (acceptingStates.contains(s))) {
                    isAccepting = true;
                }
                transitionMapping.at(s, c).stream().map(this::eps).forEach(newStates::addAll);

            }
                if (!map.containsKey(newStates)) {
                    statesQueue.add(newStates);
                    map.put(newStates, new IdentifiedState(counter++));
                }
                if (isAccepting) {
                    newAcceptingStates.add(map.get(statesQueue.peek()));
                }
                isAccepting = false;
                newTransitions.add(new Transition(map.get(statesQueue.peek()), c, map.get(newStates)));
            }
            statesQueue.poll();
        }

        try {
            return new DFSM(new HashSet<>(map.values()), alphabet, newTransitions, map.get(initialStates), newAcceptingStates);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
