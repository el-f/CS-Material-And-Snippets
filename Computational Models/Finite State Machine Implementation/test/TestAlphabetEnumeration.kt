import org.junit.jupiter.api.Assertions
import org.junit.jupiter.api.Test

class TestAlphabetEnumeration {
    @Test
    fun testFirst() {
        val alphabet = Alphabet(mutableListOf('a', 'b'))
        Assertions.assertEquals("", alphabet.first())
    }

    @Test
    fun testNext() {
        val alphabet = Alphabet(mutableListOf('a', 'b'))
        var next = alphabet.first()
        next = alphabet.next(next)
        Assertions.assertEquals("a", next)
    }

    @Test
    fun testNextNext() {
        val alphabet = Alphabet(mutableListOf('a', 'b'))
        var next = alphabet.first()
        next = alphabet.next(next)
        next = alphabet.next(next)
        Assertions.assertEquals("b", next)
    }

    @Test
    fun testNext3() {
        val alphabet = Alphabet(mutableListOf('a', 'b'))
        var next = alphabet.first()
        next = alphabet.next(next)
        next = alphabet.next(next)
        next = alphabet.next(next)
        Assertions.assertEquals("aa", next)
    }

    @Test
    fun testNext4() {
        val alphabet = Alphabet(mutableListOf('a', 'b'))
        var next = alphabet.first()
        next = alphabet.next(next)
        next = alphabet.next(next)
        next = alphabet.next(next)
        next = alphabet.next(next)
        Assertions.assertEquals("ab", next)
    }

    @Test
    fun testNext100() {
        val alphabet = Alphabet(mutableListOf('a', 'b'))
        var next = alphabet.first()
        for (i in 0..99) next = alphabet.next(next)

        /*
		
		100 + 1 - power(2, floor(log(2, 100+1)))
		= 
		101 - power(2, 6)
		=
		101 - 64
		= 
		37
		
		37 in binary is 32+4+1 = 100101
		 
		*/Assertions.assertEquals("baabab", next)
    }
}