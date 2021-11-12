import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions
import kotlin.Throws

class TestCanonicForm {
    @Test
    fun testCanonicFormOfEmptyMachine() {
        val original = "5/a b/5,b,5;5,a,5/5/"
        val canonic = "0/a b/0,a,0;0,b,0/0/"
        Assertions.assertEquals(canonic, DFSM(original).toCanonicForm().encode())
    }

    @Test
    @Throws(Exception::class)
    fun testCanonicFormNDFMS() {
        val original = "5 2 3/a b/5,a,5;5,a,2;5,,3/5/3"
        val canonic = "0 1 2/a b/0,,1;0,a,0;0,a,2/0/1"
        Assertions.assertEquals(canonic, NDFSM(original).toCanonicForm().encode())
    }
}