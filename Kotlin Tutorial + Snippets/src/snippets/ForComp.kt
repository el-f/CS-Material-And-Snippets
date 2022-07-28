import java.util.Optional

// 5a6f71185084d76d2000001b

fun <T> `for`(lambda: suspend SequenceScope<Optional<T>>.() -> Unit): Optional<T> {
    return sequence<Optional<T>> { lambda() }.first()
}

suspend fun <T> SequenceScope<Optional<T>>.yield(value: T) = yield(Optional.of(value))

suspend fun <T, U> SequenceScope<Optional<T>>.bind(value: Optional<U>): U {
    if (!value.isPresent) {
        yield(Optional.empty())
    }
    return value.get()
}

import org.junit.Ignore
import org.junit.Test
import kotlin.test.*
import java.util.Optional.empty as none
import java.util.Optional.of as some

class SimpleForComprehensionTest {

    @Test
    fun test1_IntAddition() {
        fun plus(o1: java.util.Optional<Int>,
                 o2: java.util.Optional<Int>): java.util.Optional<Int> =
                `for` {
                    val i: Int = bind(o1)
                    val j: Int = bind(o2)
                    yield(i + j)
                }

        fun testPlus(expected: java.util.Optional<Int>,
                     o1: java.util.Optional<Int>, o2: java.util.Optional<Int>) {
            val actual = plus(o1, o2)
            assert(expected == actual) { "$o1 plus $o2 should be $expected, but you give me a $actual" }
        }

        val nothing = none<Int>()
        testPlus(some(6), some(4), some(2))
        testPlus(nothing, nothing, some(2))
        testPlus(nothing, some(4), nothing)
        testPlus(nothing, nothing, nothing)
    }

    @Test
    fun test2_StringConcat() {
        /**
         * If [o1] gets empty, [o2] should never be used!
         */
        fun concat(o1: () -> java.util.Optional<String>,
                   o2: () -> java.util.Optional<String>): java.util.Optional<String> =
                `for` {
                    val i: String = bind(o1())
                    val j = " is "
                    val k: String = bind(o2())
                    yield(i + j + k)
                }

        class ThisCodeShouldBeExecuted : RuntimeException()
        class ThisCodeShouldNotBeExecuted : RuntimeException()

        val nothing = none<String>()
        assertFailsWith<ThisCodeShouldBeExecuted> { concat({ throw ThisCodeShouldBeExecuted() }, { throw ThisCodeShouldNotBeExecuted() }) }
        assertFailsWith<ThisCodeShouldBeExecuted> { concat({ some("ice1000 is julao") }, { throw ThisCodeShouldBeExecuted() }) }
        assertEquals(nothing, concat({ nothing }, { throw ThisCodeShouldNotBeExecuted() }))
        assertEquals(some("ice1000 is julao"), concat({ some("ice1000") }, { some("julao") }))
        assertEquals(nothing, concat({ some("ice1000") }, { nothing }))
        assertEquals(nothing, concat({ nothing }, { some("julao") }))
        assertEquals(nothing, concat({ nothing }, { nothing }))
    }

    @Test
    fun test3_EatRice() {
        val sb: java.util.Optional<StringBuilder> = `for` {
            val i: Int = bind(some(1551))
            val s: String = bind(`for` { yield("ywwuyi") })
            var sb: StringBuilder = bind(some(StringBuilder(100)))
            repeat(10) {
                sb = bind(some(sb.append(i).append(s)))
            }
            yield(sb)
        }
        assertEquals("1551ywwuyi".repeat(10), sb.get().toString())
    }

    @Test
//     @Ignore
    fun test4_RandomIntAddition() {
        fun plus(o1: java.util.Optional<Int>,
                 o2: java.util.Optional<Int>): java.util.Optional<Int> =
                `for` {
                    val i: Int = bind(o1)
                    val j: Int = bind(o2)
                    yield(i + j)
                }

        fun okPlus(o1: java.util.Optional<Int>, o2: java.util.Optional<Int>) =
                o1.flatMap { i1 -> o2.flatMap { i2 -> some(i1 + i2) } }

        val random = java.util.Random()
        fun getRandomInt() = java.util.Optional.ofNullable(random.nextInt(1_0000_0000).takeIf { it < (1_0000_0000 * 0.618) })

        repeat(100) {
            val o1 = getRandomInt()
            val o2 = getRandomInt()
            val expected = okPlus(o1, o2)
            val actual = plus(o1, o2)
            assert(expected == actual) { "$o1 plus $o2 should be $expected, but you give me a $actual" }
        }
    }
    
    @Test  
    fun dont_use_try_and_catch() {
        java.nio.file.Files.lines(java.io.File("/workspace/solution.txt").toPath()).forEach { s ->
            val str = s.toLowerCase()
            assertFalse("\\u" in str)
            assertFalse("try" in str)
            assertFalse("catch" in str)
            assertFalse("exception" in str)
        }
    }
}
