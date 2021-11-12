import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions

class TestMinimization {
    @Test
    fun testUnreachableStates() {
        val original = "0 1/a b/0,a,0;0,b,0;1,a,0;1,b,1/0/0"
        val minimal = "0/a b/0,a,0;0,b,0/0/0"
        Assertions.assertEquals(minimal, DFSM(original).removeUnreachableStates().encode())
    }

    @Test
    fun testRemoveUnreachableIdempotency() {
        val original = "1 2 3 4 5 6/a b/1,a,2;1,b,4;2,a,3;2,b,6;3,a,2;3,b,4;4,a,6;4,b,5;5,a,2;5,b,4;6,a,6;6,b,6/1/2 4"
        Assertions.assertEquals(original, DFSM(original).removeUnreachableStates().encode())
    }

    @Test
    fun testExample5dot28() {
        val original = "1 2 3 4 5 6/a b/1,a,2;1,b,4;2,a,3;2,b,6;3,a,2;3,b,4;4,a,6;4,b,5;5,a,2;5,b,4;6,a,6;6,b,6/1/2 4"
        val minimal = "0 1 2 3/a b/0,a,1;0,b,2;1,a,0;1,b,3;2,a,3;2,b,0;3,a,3;3,b,3/0/1 2"
        Assertions.assertEquals(minimal, DFSM(original).minimize().toCanonicForm().encode())
    }

    @Test
    fun testMinimizationIdempotency() {
        val original = "1 2 3 4 5 6/a b/1,a,2;1,b,4;2,a,3;2,b,6;3,a,2;3,b,4;4,a,6;4,b,5;5,a,2;5,b,4;6,a,6;6,b,6/1/2 4"
        val minimal = "0 1 2 3/a b/0,a,1;0,b,2;1,a,0;1,b,3;2,a,3;2,b,0;3,a,3;3,b,3/0/1 2"
        Assertions.assertEquals(minimal, DFSM(original).minimize().minimize().toCanonicForm().encode())
    }
}