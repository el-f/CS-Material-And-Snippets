package snippets

fun main() {
    for (i in 10.0..0.0 step -1.0) {
        println(i)
    }
    println("~~~~~~~")
    for (i in 0.0..10.0 step 1.0) {
        println(i)
    }
}

// Add for-loops functionality to Double ~Bidirectional~ Range
private infix fun ClosedRange<Double>.step(step: Double): Iterable<Double> {
    require(start.isFinite())
    require(endInclusive.isFinite())
    val isGoingUp = endInclusive > start
    require(if (isGoingUp) step > 0 else step < 0) {
        "Step must be signed according to range start and end! (start=$start, end=$endInclusive, step=$step)"
    }

    return generateSequence(start) {
        if (it == if (isGoingUp) Double.POSITIVE_INFINITY else Double.NEGATIVE_INFINITY) {
            null
        } else {
            val next = it + step
            if (it == endInclusive) null else next
        }
    }.asIterable()
}