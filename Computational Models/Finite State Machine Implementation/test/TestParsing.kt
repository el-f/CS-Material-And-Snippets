import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions
import kotlin.Throws

class TestParsing {
    @Test
    fun test() {
        val encoding = "0 1/a b/0,a,0;0,b,1;1,a,0;1,b,1/0/1"
        val aDFSM = DFSM(encoding)
        Assertions.assertEquals(encoding, aDFSM.encode())
    }

    @Test
    fun testNoAcceptingStates() {
        val encoding = "0/a b/0,a,0;0,b,0/0/"
        val aDFSM = DFSM(encoding)
        Assertions.assertEquals(encoding, aDFSM.encode())
    }

    @Test
    @Throws(Exception::class)
    fun testParsingEpsilonTransition() {
        val encoding = "0 1/a b/0,,0;0,b,1;1,a,0;1,b,1/0/1"
        val anNDFSM = NDFSM(encoding)
        Assertions.assertEquals(anNDFSM.encode(), encoding)
    }

    @Test
    @Throws(Exception::class)
    fun testTinyMachine() {
        val encoding = "0/a/0,,0/0/"
        val anNDFSM = NDFSM(encoding)
        Assertions.assertEquals(anNDFSM.encode(), encoding)
    }

    @Test
    @Throws(Exception::class)
    fun testWithSpaces() {
        val withSpaces =
            "0 1 2 3 4 5 6 7/a b/3,b,7; 0,a,1; 7,a,1; 3,a,6; 7,b,0; 4,b,5; 2,b,5; 1,b,3; 0,b,0; 1,a,2; 2,a,4; 4,a,4; 5,b,7; 5,a,6; 6,a,2; 6,b,3/0/4 5 6 7"
        val noSpaces =
            "0 1 2 3 4 5 6 7/a b/0,a,1;0,b,0;1,a,2;1,b,3;2,a,4;2,b,5;3,a,6;3,b,7;4,a,4;4,b,5;5,a,6;5,b,7;6,a,2;6,b,3;7,a,1;7,b,0/0/4 5 6 7"
        val anNDFSM = NDFSM(withSpaces)
        Assertions.assertEquals(anNDFSM.encode(), noSpaces)
    }
}