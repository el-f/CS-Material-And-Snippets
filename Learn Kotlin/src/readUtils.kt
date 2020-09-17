@file:Suppress("unused")

fun readln() = readLine()!!
fun readlnByte() = readln().toByte()
fun readlnShort() = readln().toShort()
fun readlnInt() = readln().toInt()
fun readlnLong() = readln().toLong()
fun readlnFloat() = readln().toFloat()
fun readlnDouble() = readln().toDouble()
fun readlnBigInt(radix: Int = 10) = readln().toBigInteger(radix)
fun readlnBigDecimal() = readln().toBigDecimal()

fun lineSequence(limit: Int = Int.MAX_VALUE) = generateSequence { readLine() }.constrainOnce().take(limit)
fun readlnStrings() = readln().split(' ')
fun readlnBytes() = readlnStrings().map { it.toByte() }
fun readlnShorts() = readlnStrings().map { it.toShort() }
fun readlnInts() = readlnStrings().map { it.toInt() }
fun readlnLongs() = readlnStrings().map { it.toLong() }
fun readlnFloats() = readlnStrings().map { it.toFloat() }
fun readlnDoubles() = readlnStrings().map { it.toDouble() }

fun readByteArray() = readlnStrings().run { ByteArray(size) { get(it).toByte() } }
fun readShortArray() = readlnStrings().run { ShortArray(size) { get(it).toShort() } }
fun readIntArray() = readlnStrings().run { IntArray(size) { get(it).toInt() } }
fun readLongArray() = readlnStrings().run { LongArray(size) { get(it).toLong() } }
fun readFloatArray() = readlnStrings().run { FloatArray(size) { get(it).toFloat() } }
fun readDoubleArray() = readlnStrings().run { DoubleArray(size) { get(it).toDouble() } }

fun readlnByteArray(n: Int) = ByteArray(n) { readlnByte() }
fun readlnShortArray(n: Int) = ShortArray(n) { readlnShort() }
fun readlnIntArray(n: Int) = IntArray(n) { readlnInt() }
fun readlnLongArray(n: Int) = LongArray(n) { readlnLong() }
fun readlnFloatArray(n: Int) = FloatArray(n) { readlnFloat() }
fun readlnDoubleArray(n: Int) = DoubleArray(n) { readlnDouble() }

fun readByteArray2d(rows: Int, cols: Int) = Array(rows) { readByteArray().also { require(it.size == cols) } }
fun readShortArray2d(rows: Int, cols: Int) = Array(rows) { readShortArray().also { require(it.size == cols) } }
fun readLongArray2d(rows: Int, cols: Int) = Array(rows) { readLongArray().also { require(it.size == cols) } }
fun readIntArray2d(rows: Int, cols: Int) = Array(rows) { readIntArray().also { require(it.size == cols) } }
fun readFloatArray2d(rows: Int, cols: Int) = Array(rows) { readFloatArray().also { require(it.size == cols) } }
fun readDoubleArray2d(rows: Int, cols: Int) = Array(rows) { readDoubleArray().also { require(it.size == cols) } }

fun isWhiteSpace(c: Char) = c in " \r\n\t"

// JVM-only targeting code follows next

// readString() via sequence is still slightly faster than Scanner
fun readString() = generateSequence { System.`in`.read().toChar() }
    .dropWhile { isWhiteSpace(it) }.takeWhile { !isWhiteSpace(it) }.joinToString("")

fun readByte() = readString().toByte()
fun readShort() = readString().toShort()
fun readInt() = readString().toInt()
fun readLong() = readString().toLong()
fun readFloat() = readString().toFloat()
fun readDouble() = readString().toDouble()
fun readBigInt(radix: Int = 10) = readString().toBigInteger(radix)
fun readBigDecimal() = readString().toBigDecimal()

fun readBytes(n: Int) = generateSequence { readByte() }.take(n)
fun readShorts(n: Int) = generateSequence { readShort() }.take(n)
fun readInts(n: Int) = generateSequence { readInt() }.take(n)
fun readLongs(n: Int) = generateSequence { readLong() }.take(n)
fun readFloats(n: Int) = generateSequence { readFloat() }.take(n)
fun readDoubles(n: Int) = generateSequence { readDouble() }.take(n)