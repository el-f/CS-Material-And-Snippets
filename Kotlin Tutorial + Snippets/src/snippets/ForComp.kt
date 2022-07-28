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
