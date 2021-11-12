import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions
import kotlin.Throws

class TestPrettyPrinting {
    @Test
    fun testBasicPrinting() {
        val encoding = "0 1/a b/0,a,0;0,b,1;1,a,0;1,b,1/0/1"
        val anDFSM = DFSM(encoding)
        anDFSM.prettyPrint(System.out)
        Assertions.assertTrue(true)
    }

    @Test
    @Throws(Exception::class)
    fun testPrintingEpsilonTransitions() {
        val encoding = "0 1/a b/0,a,0;0,b,1;1,,0;1,b,1/0/1"
        val anNDFSM = NDFSM(encoding)
        anNDFSM.prettyPrint(System.out)
        Assertions.assertTrue(true)
    }
}