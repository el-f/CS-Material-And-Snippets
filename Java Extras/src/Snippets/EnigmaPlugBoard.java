package Snippets;

import com.google.common.collect.BiMap;
import com.google.common.collect.HashBiMap;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

// my solution for this kata: 5523b97ac8f5025c45000900

public class EnigmaPlugBoard {

    static final int PAIRS_LIMIT = 10;
    BiMap<Character, Character> biMap;

    public EnigmaPlugBoard(String wires) throws InvalidPlugBoardWiresException {
        if (wires.length() % 2 != 0) throw new InvalidPlugBoardWiresException();
        if (wires.length() / 2 > PAIRS_LIMIT) throw new InvalidPlugBoardWiresException();
        biMap = HashBiMap.create();
        char[] charArray = wires.toCharArray();
        char kv, vk;
        for (int i = 0; i < charArray.length; i += 2) {
            kv = charArray[i];
            vk = charArray[i + 1];
            if (biMap.containsKey(kv) || biMap.containsKey(vk)
                    || biMap.containsValue(kv) || biMap.containsValue(vk)) {
                throw new InvalidPlugBoardWiresException();
            }
            biMap.put(charArray[i], charArray[i + 1]);
        }

    }

    public String process(String wire) {
        StringBuilder sb = new StringBuilder();
        char found;
        for (char c : wire.toCharArray()) {
            if (biMap.containsKey(c)) {
                found = biMap.get(c);
            } else if (biMap.containsValue(c)) {
                found = biMap.inverse().get(c);
            } else found = c;
            sb.append(found);
        }
        return sb.toString();
    }


}

class InvalidPlugBoardWiresException extends Exception {
}

class PlugBoardTests {
    @Test
    public void testTooManyWiresDefined() {
        assertThrows(InvalidPlugBoardWiresException.class, () -> new EnigmaPlugBoard("ABCDEFGHIJKLMNOPQRSTUV"));
    }

    @Test
    public void testNotEnoughWiresDefined() {
        assertThrows(InvalidPlugBoardWiresException.class, () -> new EnigmaPlugBoard("ABCDEFGHIJKLMNOPQ"));
    }

    @Test
    public void testMultipleWiresDefined() {
        assertThrows(InvalidPlugBoardWiresException.class, () -> new EnigmaPlugBoard("ABCA"));
    }

    @Test
    public void testTranslateCharacters() throws InvalidPlugBoardWiresException {
        EnigmaPlugBoard plugboard = new EnigmaPlugBoard("ABCDEFGHIJKLMNOPQRST");
        assertEquals("B", plugboard.process("A"));
        assertEquals("A", plugboard.process("B"));
        assertEquals("S", plugboard.process("T"));
        assertEquals("T", plugboard.process("S"));
        assertEquals("Z", plugboard.process("Z"));
    }

    @Test
    public void testTranslateMessage1() throws InvalidPlugBoardWiresException {
        EnigmaPlugBoard plugboard = new EnigmaPlugBoard("ABCDEFGHIJZYXWVUTSRQ");
        assertEquals("SGF FNJHMB MBDGJNF DBNNOS AF DQBDKFC", plugboard.process("THE ENIGMA MACHINE CANNOT BE CRACKED"));
    }

    @Test
    public void testReverseTranslateMessage1() throws InvalidPlugBoardWiresException {
        EnigmaPlugBoard plugboard = new EnigmaPlugBoard("ABCDEFGHIJZYXWVUTSRQ");
        assertEquals("THE ENIGMA MACHINE CANNOT BE CRACKED", plugboard.process("SGF FNJHMB MBDGJNF DBNNOS AF DQBDKFC"));
    }


}


