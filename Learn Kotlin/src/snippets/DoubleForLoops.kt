package snippets

import kotlin.math.abs

fun main() {
    for (i in 10.0..0.0 step -0.5) {
        print("$i, ")
    }
    println("\n~~~~~~~")
    for (i in 0.0..10.0 step 1.00003) {
        print("$i, ")
    }
}

// Add for-loops functionality to Double ~Bidirectional~ Range
infix fun ClosedRange<Double>.step(step: Double): Iterable<Double> {
    require(start.isFinite())
    require(endInclusive.isFinite())
    val isGoingUp = endInclusive > start
    require(start != endInclusive) { "start can't be also the end! (start=$start, end=$endInclusive, step=$step)" }
    require(if (isGoingUp) step > 0 else step < 0) {
        "Step must be signed according to range start and end! (start=$start, end=$endInclusive, step=$step)"
    }
    require(abs(step) >= 1.0E-10) { "step can't be more precise than 1.0E-10" }

    return generateSequence(start) { current ->
        when {
            current == if (isGoingUp) Double.POSITIVE_INFINITY else Double.NEGATIVE_INFINITY -> null
            if (isGoingUp) current >= endInclusive else current <= endInclusive -> null
            if (isGoingUp) current + step > endInclusive else current + step < endInclusive -> null
            else -> String.format("%.10f", current + step).toDouble()
        }
    }.asIterable()
}