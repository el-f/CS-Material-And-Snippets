# Interview Questions
 
## Kotlin

### Q1: What is a primary constructor in Kotlin? ☆☆

**Answer:**
The **primary constructor** is part of the class header. Unlike Java, you don't need to declare a constructor in the body of the class. Here's an example:

```kotlin
class Person(val firstName: String, var age: Int) {
    // class body
}
```

The main idea is by removing the constructor keyword, our code gets simplified and easy to understand.

**Source:** _www.programiz.com_
### Q2: What is a data class in Kotlin? ☆☆

**Answer:**
We frequently create classes whose main purpose is to hold data. In Kotlin, this is called a data class and is marked as `data`:

```kotlin
data class User(val name: String, val age: Int)
```

To ensure consistency and meaningful behavior of the generated code, data classes have to fulfill the following requirements:

* The primary constructor needs to have at least one parameter;
* All primary constructor parameters need to be marked as val or var;
* Data classes cannot be abstract, open, sealed or inner;

**Source:** _kotlinlang.org_
### Q3: Explain the Null safety in Kotlin ☆☆☆

**Answer:**
Kotlin's type system is aimed at eliminating the danger of null references from code, also known as the The Billion Dollar Mistake.

One of the most common pitfalls in many programming languages, including Java, is that accessing a member of a null reference will result in a null reference exception. In Java this would be the equivalent of a `NullPointerException` or NPE for short.

In Kotlin, the type system distinguishes between references that can hold `null` (nullable references) and those that can not (`non-null` references). For example, a regular variable of type String can not hold null:

```kotlin
var a: String = "abc"
a = null // compilation error
```
To allow nulls, we can declare a variable as nullable string, written `String?`:
```kotlin
var b: String? = "abc"
b = null // ok
print(b)
```

**Source:** _kotlinlang.org_
### Q4: How are extensions resolved in Kotlin and what doest it mean? ☆☆☆

**Answer:**
Extensions do not actually modify classes they extend. By defining an extension, you do not insert new members into a class, but merely make new functions callable with the dot-notation on variables of this type.

The extension functions dispatched **statically**. That means the extension function which will be called is determined by the type of the expression on which the function is invoked, not by the type of the result of evaluating that expression at runtime. In short, they are not virtual by receiver type.

Consider:
```kotlin
open class BaseClass

class DerivedClass : BaseClass()

fun BaseClass.someMethod(){
    print("BaseClass.someMethod")
}

fun DerivedClass.someMethod(){
    print("DerivedClass.someMethod")
}

fun printMessage(base : BaseClass){
    base.someMethod()
}

printMessage(DerivedClass())
```

This will print 

```sh
BaseClass.someMethod
```

because the extension function being called depends only on the declared type of the parameter `base` in `printMessage` method, which is the `BaseClass` class. This is different from runtime polymorphism as here it is resolved **statically** but not at the runtime.

**Source:** _medium.com_
### Q5: What is a purpose of Companion Objects in Kotlin? ☆☆☆

**Answer:**
Unlike Java or C#, Kotlin doesn’t have `static` members or member functions. If you need to write a function that can be called without having a class instance but needs access to the internals of a class, you can write it as a member of a **companion object** declaration inside that class.

```kotlin
class EventManager {

    companion object FirebaseManager {
    }  
}

val firebaseManager = EventManager.FirebaseManager
```

The companion object is a singleton. The companion object is a **proper object** on its own, and can have its own supertypes - and you can assign it to a variable and pass it around. If you're integrating with Java code and need a true static member, you can annotate a member inside a companion object with `@JvmStatic`.

**Source:** _kotlinlang.org_
### Q6: What is Lateinit in Kotlin and when would you use it? ☆☆☆

**Answer:**
**lateinit** means _late initialization_. If you do not want to initialize a variable in the constructor instead you want to initialize it later on and if you can guarantee the initialization before using it, then declare that variable with lateinit keyword. It will not allocate memory until initialized. You cannot use lateinit for primitive type properties like Int, Long etc.

```kotlin
lateinit var test: String

fun doSomething() {
    test = "Some value"
    println("Length of string is "+test.length)
    test = "change value"
}
```

There are a handful of use cases where this is extremely helpful, for example:

* Android: variables that get initialized in lifecycle methods;
* Using Dagger for DI: injected class variables are initialized outside and independently from the constructor;
* Setup for unit tests: test environment variables are initialized in a `@Before` - annotated method;
* Spring Boot annotations (eg. `@Autowired`).

**Source:** _medium.com_
### Q7: Explain lazy initialization in Kotlin ☆☆☆

**Answer:**
**lazy** means lazy initialization. Your variable will not be initialized unless you use that variable in your code. It will be initialized only once after that we always use the same value.

`lazy()` is a function that takes a lambda and returns an instance of lazy which can serve as a delegate for implementing a lazy property: the first call to `get()` executes the lambda passed to `lazy()` and remembers the result, subsequent calls to `get() `simply return the remembered result.

```kotlin
val test: String by lazy {
    val testString = "some value"
}
```

**Source:** _blog.mindorks.com_
### Q8: When to use lateinit over lazy initialization in Kotlin? ☆☆☆

**Answer:**


There are some simple rules to determined if you should use one or the other for properties initialisation:
* If properties are mutable (i.e. might change at a later stage) use **lateInit**
* If properties are set externally (e.g. need to pass in some external variable to set it), use **lateinit**. There’s still workaround to use lazy but not as direct.
* If they are only meant to initialized once and shared by all, and it’s more internally set (dependent on variable internal to the class), then use **lazy**. Tactically, you could still use lateinit, but using** lazy** would better encapsulate your initialization code.


Also compare:

|||
|--- |--- |
|**lateinit** var|by **lazy**|
|Can be initialized from anywhere the object seen from.|Can only be initialized from the initializer lambda.|
|Multiple initialization possible.|Only initialize single time.|
|Non-thread safe. It’s up to user to initialize correctly in a multi-threaded environment.|Thread-safety by default and guarntees that the initializer is invoked by once.|
|Can only be used for var.|Can only be used for val.|
|Not eligible for nonnull properties.|Not eligible for nonnull properties.|
|An isInitialized method added to check whether the value has been initialized before.|Property never able to un-initialized.|
|Not allowed on properties of primitive types.|Allowed on properties of primitive types.|

**Source:** _ahsensaeed.com_
### Q9: May you briefly compare Kotlin vs Java? ☆☆☆

**Answer:**
||||
|--- |--- |--- |
|Java vs Kotlin|Java|Kotlin|
|Null Safe|In Java, `NullPointerExceptions` causes huge frustration for developers. It allows users to assign null to any variables but while accessing an object reference having null value raises a null pointer exception which user needs to handle.|In Kotlin, By default, all types of variables are non-null able (i.e. we can’t assign null values to any type of variables/objects). If we try to assign or return null values, Kotlin code will fail during compile-time. If we really want a variable to have a null value, we can declare as follows: `value num: Int? = null`|
|Extension Functions|In Java, If we want to extend the functionality of existing class we need to create a new class and inherit the parent class. So Extension functions are not available in Java|Kotlin provides developers the ability to extend an existing class with new functionality. We can create extend functions by prefixing the name of a class to name of the new function.|
|Coroutines Support|In Java, whenever if we initiate a long-running network I/0 or CPU Intensive operations, the corresponding thread will be blocked. As Android is a single-threaded by default. Java provides the ability to create multiple threads in the background and run but managing them is a complex task.|In Kotlin, We can create multiple threads to run these long-running intensive operations but we have coroutines support, which will suspend execution at a certain point without blocking threads while executing long-running intensive operations.|
|No checked exceptions|In Java, We have checked exceptions support which makes developers declare and catch the exception which ultimately leads to robust code with good error handling.|In Kotlin, we don’t have checked exceptions. So developers don’t need to declare or catch the exceptions, which have advantages and disadvantages.|
|Data classes|In Java, suppose we need to have a class which needs to hold data but nothing else. For this we need to define constructors, variables to store data, getter and setter methods, hashcode(), toString(), and equals() functions|In Kotlin, If we need to have classes which need to hold data we can declare a class with keyword “data” in the class definition then the compiler will take care of all of this work such as creating constructors, getter, setter methods for different fields.|
|Smart casts|In Java, We need to check the type of variables and cast according to our operation.|In Kotlin, smart casts will handle these casting checks with keyword “is-checks” which will check for immutable values and performs implicit casting.|
|Type inference|In Java, we need to specify a type of each variable explicitly while declaring.|In Kotlin, we don’t need to specify the type of each variable explicitly based on assignment it will handle. If we want to specify explicitly we can do.|
|Functional Programming|Java doesn’t have functional programming support till Java 8 but while developing Android applications it supports the only subset of Java 8 features.|Kotlin is a mix of procedural and functional programming language which consists of many useful methods such as lambda, operator overloading, higher-order functions, and lazy evaluation, etc.|

**Source:** _www.educba.com_
### Q10: What are coroutines in Kotlin? ☆☆☆

**Answer:**
Unlike many other languages with similar capabilities, async and await are not keywords in Kotlin and are not even part of its standard library. 

`kotlinx.coroutines` is a rich library for coroutines developed by JetBrains. It contains a number of high-level coroutine-enabled primitives, including `launch`, `async` and others. Kotlin Coroutines give you an API to write your asynchronous code sequentially. 

The documentation says Kotlin Coroutines are like lightweight threads. They are lightweight because creating coroutines doesn’t allocate new threads. Instead, they use predefined thread pools, and smart scheduling. Scheduling is the process of determining which piece of work you will execute next.

Additionally, coroutines can be **suspended** and **resumed** mid-execution. This means you can have a long-running task, which you can execute little-by-little. You can pause it any number of times, and resume it when you’re ready again. 

**Source:** _www.raywenderlich.com_
### Q11: How to initialize an array in Kotlin with values? ☆☆

**Details:**
In Java an array can be initialized such as:

```java
 int numbers[] = new int[] {10, 20, 30, 40, 50}
```

How does Kotlin's array initialization look like?

**Answer:**
```kotlin
val numbers: IntArray = intArrayOf(10, 20, 30, 40, 50)
```

**Source:** _stackoverflow.com_
### Q12: What is the difference between var and val in Kotlin? ☆☆

**Answer:**
* **var** is like `general` variable and it's known as a _mutable_ variable in kotlin and can be assigned multiple times.

* **val** is like `Final` variable and it's known as _immutable_ in Kotlin and can be initialized only single time.

```sh
+----------------+-----------------------------+---------------------------+
|                |             val             |            var            |
+----------------+-----------------------------+---------------------------+
| Reference type | Immutable(once initialized  | Mutable(can able to change|
|                | can't be reassigned)        | value)                    |
+----------------+-----------------------------+---------------------------+
| Example        | val n = 20                  | var n = 20                |
+----------------+-----------------------------+---------------------------+
| In Java        | final int n = 20;           | int n = 20;               |
+----------------+-----------------------------+---------------------------+
```

**Source:** _stackoverflow.com_
### Q13: How to correctly concatenate a String in Kotlin? ☆☆

**Answer:**
In Kotlin, you can concatenate 
1. using string interpolation / templates
 ```kotlin
val a = "Hello"
val b = "World"
val c = "$a $b"
 ```
2. using the + / `plus()` operator
 ```kotlin
 val a = "Hello"
 val b = "World" 
 val c = a + b   // same as calling operator function a.plus(b)
 val c = a.plus(b)
 
 print(c)
 ```
3. using the `StringBuilder`
 ```kotlin
 val a = "Hello"
 val b = "World"
 
 val sb = StringBuilder()
 sb.append(a).append(b)
 val c = sb.toString()
 
 print(c)
 ```

**Source:** _stackoverflow.com_
### Q14: What is basic difference between fold and reduce in Kotlin? When to use which? ☆☆

**Answer:**
* `fold` takes an initial value, and the first invocation of the lambda you pass to it will receive that initial value and the first element of the collection as parameters.

 ```kotlin 
 listOf(1, 2, 3).fold(0) { sum, element -> sum + element }
 ```
 The first call to the lambda will be with parameters `0` and `1`.

 Having the ability to pass in an initial value is useful _if you have to provide some sort of default value or parameter for your operation_.

* `reduce` doesn't take an initial value, but instead starts with the first element of the collection as the accumulator (called `sum` in the following example)

 ```kotlin
 listOf(1, 2, 3).reduce { sum, element -> sum + element }
 ```

 The first call to the lambda here will be with parameters `1` and `2`.

**Source:** _stackoverflow.com_
### Q15: What is the idiomatic way to remove duplicate strings from array? ☆☆

**Details:**
How to remove duplicates from an `Array<String?>` in Kotlin?

**Answer:**
Use the `distinct` extension function:

```kotlin
val a = arrayOf("a", "a", "b", "c", "c")
val b = a.distinct() // ["a", "b", "c"]
```

You can also use:
* `toSet`, `toMutableSet`
* `toHashSet` - if you don't need the original ordering to be preserved

These functions produce a `Set` instead of a `List` and should be a little bit more efficient than distinct.

**Source:** _stackoverflow.com_
### Q16: How to create singleton in Kotlin? ☆☆

**Answer:**
Just use `object`.
```kotlin
object SomeSingleton
```
The above Kotlin object will be compiled to the following equivalent Java code:
```java
public final class SomeSingleton {
   public static final SomeSingleton INSTANCE;

   private SomeSingleton() {
      INSTANCE = (SomeSingleton)this;
      System.out.println("init complete");
   }

   static {
      new SomeSingleton();
   }
}
```
This is the preferred way to implement singletons on a JVM because it enables thread-safe lazy initialization without having to rely on a locking algorithm like the complex double-checked locking.

**Source:** _medium.com_
### Q17: Where should I use var and where val? ☆☆

**Answer:**
Use **var** where value is changing _frequently_. For example while getting location of android device:

```kotlin
var integerVariable : Int? = null
```

Use **val** where there is _no change_ in value in whole class. For example you want set textview or button's text programmatically.

```kotlin
val stringVariables : String = "Button's Constant or final Text"
```

**Source:** _stackoverflow.com_
### Q18: Explain what is wrong with that code? ☆☆☆

**Details:**
Why is this code wrong?

```kotlin
class Student (var name: String) {
    init() {
        println("Student has got a name as $name")
    }

    constructor(sectionName: String, var id: Int) this(sectionName) {
    }
}
```

**Answer:**
The property of the class can’t be declared inside the secondary constructor.. This will give an error because here we are declaring a property `id` of the class in the secondary constructor, which is not allowed.

If you want to use some property inside the secondary constructor, then declare the property inside the class and use it in the **secondary constructor**:

```kotlin
class Student (var name: String) {

    var id: Int = -1
    init() {
        println("Student has got a name as $name")
    }
    
    constructor(secname: String, id: Int) this(secname) {
        this.id = id
    }
}
```

**Source:** _www.programiz.com_
### Q19: What will be result of the following code execution? ☆☆☆

**Details:**
What will be the output?
```kotlin
val aVar by lazy {
    println("I am computing this value")
    "Hola"
}
fun main(args: Array<String>) {
    println(aVar)
    println(aVar)
}
```

**Answer:**
For `lazy` the first time you access the Lazy property, the initialisation (`lazy()` function invocation) takes place. The second time, this value is remembered and returned:

```sh
I am computing this value
Hola
Hola
```

**Source:** _dzone.com_
### Q20: What is the difference between suspending vs. blocking? ☆☆☆

**Answer:**
* A **blocking** call to a function means that a call to any other function, from the same thread, will halt the parent’s execution. Following up, this means that if you make a blocking call on the main thread’s execution, you effectively freeze the UI. Until that blocking calls finishes, the user will see a static screen, which is not a good thing.

* **Suspending** doesn’t necessarily block your parent function’s execution. If you call a suspending function in some thread, you can easily push that function to a different thread. In case it is a heavy operation, it won’t block the main thread. If the suspending function has to suspend, it will simply pause its execution. This way you free up its thread for other work. Once it’s done suspending, it will get the next free thread from the pool, to finish its work.

**Source:** _www.raywenderlich.com_

### Q1: What is the equivalent of Java static methods in Kotlin? ☆☆☆

**Answer:**
Place the function in the **companion object**.

```java
class Foo {
  public static int a() { return 1; }
}
```
will become:
```kotlin
class Foo {
  companion object {
     fun a() : Int = 1
  }
}

// to run
Foo.a();
```

Another way is to solve most of the needs for static functions with package-level functions. They are simply declared outside a class in a source code file. The package of a file can be specified at the beginning of a file with the package keyword. Under the hood these "top-level" or "package" functions are actually compiled into their own class. In the above example, the compiler would create a class FooPackage with all of the top-level properties and functions, and route all of your references to them appropriately.

Consider:
```kotlin
package foo

fun bar() = {}
```
usage:
```kotlin
import foo.bar
```


**Source:** _stackoverflow.com_
### Q2: What is suspending function in Kotlin? ☆☆☆

**Answer:**
A **suspending function** is just a regular Kotlin function with an additional suspend modifier which indicates that the function can suspend the execution of a coroutine without blocking the current thread. This means that the code you are looking at might stop executing at the moment it calls a suspending function, and will resume at some later time. However, it doesn’t say anything about what the current thread will do in the meantime.

Suspending functions can invoke any other regular functions, but to actually suspend the execution, it has to be another suspending function.A suspending function cannot be invoked from a regular function, therefore several so-called coroutine builders are provided, which allow calling a suspending function from a regular non-suspending scope like `launch`, `async`, `runBlocking`.

**Source:** _proandroiddev.com_
### Q3: Explain advantages of "when" vs "switch" in Kotlin ☆☆☆

**Answer:**


In Java we use switch but in Kotlin, that switch gets converted to **when**. When has a better design. It is more concise and powerful than a traditional **switch**. **when** can be used either as an expression or as a statement.

Some examples of **when** usage:
* Two or more choices
```kotlin
when(number) {
    1 -> println("One")
    2, 3 -> println("Two or Three")
    4 -> println("Four")
    else -> println("Number is not between 1 and 4")
}
```
* "when" without arguments
```kotlin
when {
    number < 1 -> print("Number is less than 1")
    number > 1 -> print("Number is greater than 1")
}
```
* Any type passed in "when"
```kotlin
fun describe(obj: Any): String =
    when (obj) {
      1 -> "One"
      "Hello" -> "Greeting"
      is Long -> "Long"
      !is String -> "Not a string"
      else -> "Unknown"
    }
```
* Smart casting
```kotlin
when (x) {
    is Int -> print("X is integer")
    is String -> print("X is string")
}
```
* Ranges
```kotlin
when(number) {
    1 -> println("One") //statement 1
    2 -> println("Two") //statement 2
    3 -> println("Three") //statement 3
    in 4..8 -> println("Number between 4 and 8") //statement 4
    !in 9..12 -> println("Number not in between 9 and 12") //statement 5
    else -> println("Number is not between 1 and 8") //statement 6
}
```

**Source:** _blog.mindorks.com_
### Q4: What are the advantages of Kotlin over Java? ☆☆☆

**Answer:**
Basically for me less thinking required to write kotlin equivalent to most java code:

`data class`

*   java: you have to write getters and setters for each thing, you have to write `hashCode` properly (or let IDE auto generate, which you have to do again every time you change the class), `toString` (same problem as `hashcode`) and `equals` (same problem as `hashCode`). or you could use lombok, but that comes with some quirky problems of its own. `record` types are hopefully on the way. \*kotlin: `data class` does it all for you.
    

getter and setter patterns

*   java: rewrite the getter and setter for each variable you use it for
    
*   kotlin: don't have to write getter and setter, and custom getter and setter take a lot less typing in kotlin if you do want to. also delegates exist for identical getters\\setters
    

`abstract` vs `open` classes

*   java: you have to make an abstract class implementation
    
*   kotlin: `open class` lets you make an inheritable class while also being usable itself. nice mix of interface and regular class imo
    

extension functions

*   java: doesnt exist
    
*   kotlin: does exist, makes functions more clear in usage and feels more natural.
    

null

*   java: Anything but primitives can be null at any time.
    
*   kotlin: you get to decide what can and cant be null. allows for nice things like `inline class`
    

singleton

*   java: Memorize singleton pattern
    
*   kotlin: `object` instead of `class`
    

generics

*   java: Theyre alright, nothing fancy
    
*   kotlin: Reified generics (you can access the actual type), `in` and `out` for covariance
    

named parameters

*   java: does not exist, easy to break api back-compatibility if you arent careful.
    
*   kotlin: does exist, easy to preserve api back-compatiblity.
    

primary constructor

*   java: does not have per-se, you still have to define everything inside the class
    
*   kotlin: very nice to be able to quickly write a constructor without any constructor function or extra needless declarations

**Source:** _www.reddit.com_
### Q5: What are some disadvantages of Kotlin? ☆☆☆

**Answer:**
Some think that Kotlin is a mess of extra syntax and keywords. Here are a few keywords which have non-obvious meanings: internal, crossinline, expect, reified, sealed, inner, open. Java has none of these. Kotlin is also amusingly inconsistent in its keywords: a function is is declared with ‘fun’, but an interface is declared with ‘interface’ (not ‘inter’?). Kotlin also doesn’t have checked exceptions. Checked exceptions have become unfashionable, yet many (including me) find them a powerful way to ensure that your code is robust. Finally, Kotlin hides a lot of what goes on. In Java, you can trace through almost every step of program logic. This can be vital for hunting down bugs. In Kotlin, if you define a data class, then getters, setters, equality testing, to string, and hash code are added for you invisibly. This can be a bad idea.

Also according docs, what Java has that Kotlin does not:
* Checked exceptions
* Primitive types that are not classes
* Static members
* Non-private fields
* Wildcard-types
* Ternary-operator a ? b : c

**Source:** _www.quora.com_
### Q6: What is the difference between "open" and "public" in Kotlin? ☆☆☆

**Answer:**
* The **open** keyword means “open for extension“. The open annotation on a class is the opposite of Java's `final`: _it allows others to inherit from this class_.
* If you do not specify any visibility modifier, **public** is used by default, which means that your declarations will be visible everywhere. **public** is the default if nothing else is specified explicitly.

**Source:** _stackoverflow.com_
### Q7: What is the difference between “const” and “val”? ☆☆☆

**Answer:**
`const`s are compile time constants. Meaning that their value has to be assigned during compile time, unlike `val`s, where it can be done at runtime.


This means, that `const`s can never be assigned to a function or any class constructor, but only to a `String` or primitive.

For example:

```kotlin
const val foo = complexFunctionCall()   //Not okay
val fooVal = complexFunctionCall()      //Okay
 
const val bar = "Hello world"           //Also okay
```

**Source:** _stackoverflow.com_
### Q8: How to convert List to Map in Kotlin? ☆☆☆

**Answer:**
You have two choices:

* The first and most performant is to use `associateBy` function that takes two lambdas for generating the key and value, and inlines the creation of the map:

 ```kotlin
val map = friends.associateBy({it.facebookId}, {it.points})
```

* The second, less performant, is to use the standard `map` function to create a list of `Pair` which can be used by `toMap` to generate the final map:

 ```kotlin
val map = friends.map { it.facebookId to it.points }.toMap()
```

**Source:** _stackoverflow.com_
### Q9: What is the idiomatic way to deal with nullable values, referencing or converting them? ☆☆☆

**Details:**
If I have a nullable type `Xyz?`, I want to reference it or convert it to a non-nullable type `Xyz`. What is the idiomatic way of doing so in Kotlin?

**Answer:**
You have several options:

```kotlin
val something: Xyz? = createPossiblyNullXyz()

// access it as non-null asserting that with a sure call
// throws an exception if the value is null
val result1 = something!!.foo()

// access it only if it is not null using safe operator, 
// returning null otherwise
val result2 = something?.foo()

// access it only if it is not null using safe operator, 
// otherwise a default value using the elvis operator
val result3 = something?.foo() ?: differentValue

// null check it with `if` expression and then use the value, 
// similar to result3 but for more complex cases harder to do in one expression
val result4 = if (something != null) {
                   something.foo() 
              } else { 
                   ...
                   differentValue 
              }

// null check it with `if` statement doing a different action
if (something != null) { 
    something.foo() 
} else { 
    someOtherAction() 
}
```

**Source:** _stackoverflow.com_
### Q10: What is the difference between List and Array types? ☆☆☆

**Answer:**
The major difference from usage side is that `Arrays` have a fixed size while `(Mutable)List `can adjust their size dynamically. Moreover `Array` is mutable whereas `List` is not.

Furthermore `kotlin.collections.List` is an interface implemented among others by `java.util.ArrayList`. It's also extended by `kotlin.collections.MutableList `to be used when a collections that allows for item modification is needed.

On the jvm level `Array` is represented by arrays. `List` on the other hand is represented by `java.util.List` since there are no immutable collections equivalents available in Java.

**Source:** _stackoverflow.com_
### Q11: val mutableList vs var immutableList. When to use which in Kotlin? ☆☆☆

**Answer:**
Mutable and immutable list increase the design clarity of the model. <br>
This is to force developer to think and clarify the purpose of collection.

 1. If the collection will change as part of design, use mutable collection
 2. If model is meant only for viewing, use immutable list

Purpose of `val` and `var` is different from immutable and mutable list. <br>
***`val`*** and ***`var`*** keyword talk about the how a value/reference of a variable should be treated.

 - ***`var`*** - value/reference assigned to a variable can be changed at any point of time.
 - ***`val`*** - value/reference can be assigned only once to a variable and can't be changed later point in the execution.

There are several reasons why immutable objects are often preferable:

* They encourage functional programming, where state is not mutated, but passed on to the next function which creates a new state based on it. This is very well visible in the Kotlin collection methods such as map, filter, reduce, etc.
* A program without side effects is often easier to understand and debug (you can be sure that the value of an object will always be the one at its definition).
* In multithreaded programs, immutable resources cannot cause race conditions, as no write access is involved.

You have also some disadvantages:

* Copying entire collections just to add/remove a single element is computationally expensive.
* In some cases, immutability can make the code more complex, when you tediously need to change single fields. In Kotlin, data classes come with a built-in copy() method where you can copy an instance, while providing new values for only some of the fields.

**Source:** _stackoverflow.com_
### Q12: What is a difference between a class and object in Kotlin? ☆☆☆

**Answer:**
* An **object** is a singleton. You do not need to create an instance to use it.
* A **class** needs to be instantiated to be used.

The primary use case of `object` in Kotlin is because Kotlin tries to do away with static, and primitives, leaving us with a purely object oriented language. Kotlin still uses `static` and primitives underneath the hood, but it discourages devs to use those concepts any more. Instead, now Kotlin replaces static with singleton object instances. Where you would previously use static field in Java, in Kotlin you will now create an `object`, and put that field in the `object`.

**Source:** _stackoverflow.com_
### Q13: How is it recommended to create constants in Kotlin? ☆☆☆

**Answer:**
In Kotlin, if you want to create the local constants which are supposed to be used with in the class then you can create it like below:

```kotlin
val MY_CONSTANT_1 = "Constants1"
// or 
const val MY_CONSTANT_2 = "Constants2"
```

Like `val`, variables defined with the `const` keyword are immutable. The difference here is that **const is used for variables that are known at compile-time**.

Also avoid using companion objects. Behind the hood, getter and setter instance methods are created for the fields to be accessible. Calling instance methods is technically more expensive than calling static methods. Instead define the constants in `object`:

```kotlin
object DbConstants {
        const val TABLE_USER_ATTRIBUTE_EMPID = "_id"
        const val TABLE_USER_ATTRIBUTE_DATA = "data"
}
```

**Source:** _stackoverflow.com_
### Q14: May you use IntArray and an Array<Int> is in Kotlin interchangeably? ☆☆☆

**Answer:**
`Array<Int>` is an `Integer[]` under the hood, while `IntArray` is an `int[]`. 

This means that when you put an `Int` in an `Array<Int>`, it will always be boxed (specifically, with an `Integer.valueOf()` call). In the case of `IntArray`, no boxing will occur, because it translates to a Java primitive array.

So **no**, we can't use them interchangeably.

<div class="text-center"/>
<img src="https://i.stack.imgur.com/rwdMu.png" class="img-fluid" />
</div>


**Source:** _stackoverflow.com_
### Q15: Rewrite this code in Kotlin ☆☆☆

**Details:**
Can you rewrite this Java code in Kotlin?
```java
public class Singleton {
    private static Singleton instance = null;
    private Singleton(){
    }
    private synchronized static void createInstance() {
        if (instance == null) {
            instance = new Singleton();
        }
    }
    public static Singleton getInstance() {
        if (instance == null) createInstance();
        return instance;
    }

```

**Answer:**
Using Kotlin:
```kotlin
object Singleton
```

**Source:** _antonioleiva.com_
### Q16: How would you create a singleton with parameter in Kotlin? ☆☆☆

**Answer:**
Because a Kotlin `object` can’t have any constructor, you can’t pass any argument to it.

So look at this code from Google's architecture components sample code, which uses the `also` function:

```kotlin
class UsersDatabase : RoomDatabase() {

    companion object {

        @Volatile private var INSTANCE: UsersDatabase? = null

        fun getInstance(context: Context): UsersDatabase =
            INSTANCE ?: synchronized(this) {
                INSTANCE ?: buildDatabase(context).also { INSTANCE = it }
            }

        private fun buildDatabase(context: Context) =
            Room.databaseBuilder(context.applicationContext,
                    UsersDatabase::class.java, "Sample.db")
                    .build()
    }
}
```

**Source:** _stackoverflow.com_
### Q17: What is the Kotlin double-bang (!!) operator? ☆☆☆

**Answer:**
The **not-null assertion operator !!** converts any value to a non-null type and throws a `KotlinNullPointerException` exception if the value is null.

Consider:
```kotlin
fun main(args: Array<String>) {
    var email: String?
    email = null
    println(email!!)
}
```
This operator should be used in cases where the developer is guaranteeing – it allows you to be 100% sure that its value is not null. 

**Source:** _stackoverflow.com_
### Q18: What is the purpose of Unit-returning in functions? Why is VALUE there? What is this VALUE? ☆☆☆

**Details:**
Explain what is the purpose of Unit-returning in functions? Why is VALUE there? What is this VALUE?
```kotlin
fun printHello(name : String?) : Unit { 
   if (name != null) 
     print("Hello, $name!") 
   else 
     print("Hi there!") 
   // We don't need to write 'return Unit.VALUE' or 'return', although we could 
}
```

**Answer:**
The purpose is the same as C's or Java's `void`. Only Unit is a proper type, so it can be passed as a generic argument etc.

1. Why we don't call it "Void": because the word "void" means "nothing", and there's another type, `Nothing`, that means just "no value at all", i.e. the computation did not complete normally (looped forever or threw an exception). We could not afford the clash of meanings.

2. Why Unit has a value (i.e. is not the same as Nothing): because generic code can work smoothly then. If you pass Unit for a generic parameter T, the code written for any T will expect an object, and there must be an object, the sole value of Unit.

3. How to access that value of Unit: since it's a singleton object, just say `Unit`

4. `UNIT` actually contains valuable information, it basically just means "DONE". It just returns the information to the caller, that the method has been finished. 

**Source:** _stackoverflow.com_
### Q19: When would you use Elvis operator in Kotlin? ☆☆☆

**Answer:**
The Elvis operator is part of many programming languages, e.g. Kotlin but also Groovy or C#. The Elvis operator is the ternary operator with its second operand omitted.

```kotlin
x ?: y // yields `x` if `x` is not null, `y` otherwise.
```
If `x` isn't null, then it will be returned. If it is null, then the `y` will be returned. 

**Source:** _kotlinlang.org_
### Q40: What are scope functions in Kotlin? ☆☆☆

**Answer:**
The Kotlin standard library contains several functions whose sole purpose is to execute a block of code within the context of an object. When you call such a function on an object with a lambda expression provided, it forms a temporary scope. In this scope, you can access the object without its name. Such functions are called **scope functions**. 

There are five of them: 
* `let`, 
* `run`, 
* `with`, 
* `apply`,
* `also`.

**Source:** _stackoverflow.com_

### Q1: Why is there no static keyword in Kotlin? ☆☆☆☆

**Answer:**
_The main advantage of this is that everything is an object_. Companion objects can inherit from other classes or implement interfaces and generally behave like any other singleton.

In Java, static members are treated very differently than object members. This means that you can't do things like implementing an interface or putting your class "instance" into a map or pass it as a parameter to a method that takes Object. Companion objects allow for these things. That's the advantage.

**Source:** _softwareengineering.stackexchange.com_
### Q2: What is inline class in Kotlin and when do we need one? Provide an example. ☆☆☆☆

**Answer:**
Sometimes it is necessary for business logic to create a wrapper around some type. However, it introduces runtime overhead due to additional heap allocations. Moreover, if the wrapped type is primitive, the performance hit is terrible, because primitive types are usually heavily optimized by the runtime.

**Inline classes** provide us with a way to wrap a type, thus adding functionality and creating a new type by itself. As opposed to regular (non-inlined) wrappers, they will benefit from improved performance. This happens because the data is inlined into its usages, and object instantiation is skipped in the resulting compiled code.

```kotlin
inline class Name(val s: String) {
    val length: Int
        get() = s.length

    fun greet() {
        println("Hello, $s")
    }
}    

fun main() {
    val name = Name("Kotlin")
    name.greet() // method `greet` is called as a static method
    println(name.length) // property getter is called as a static method
}
```

Some notes about inline classes:
* A single property initialized in the primary constructor is the basic requirement of an inline class
* Inline classes allow us to define properties and functions just like regular classes
* Init blocks, inner classes, and backing fields are not allowed
* Inline classes can inherit only from interfaces
* Inline classes are also effectively final


**Source:** _www.baeldung.com_
### Q3: Explain the difference between Inline classes vs type aliases ☆☆☆☆

**Answer:**
The crucial difference is that type aliases are **assignment-compatible** with their underlying type (and with other type aliases with the same underlying type), while inline classes are not.

In other words, inline classes introduce a truly new type, contrary to type aliases which only introduce an alternative name (alias) for an existing type:

```kotlin
typealias NameTypeAlias = String
inline class NameInlineClass(val s: String)

fun acceptString(s: String) {}
fun acceptNameTypeAlias(n: NameTypeAlias) {}
fun acceptNameInlineClass(p: NameInlineClass) {}

fun main() {
    val nameAlias: NameTypeAlias = ""
    val nameInlineClass: NameInlineClass = NameInlineClass("")
    val string: String = ""

    acceptString(nameAlias) // OK: pass alias instead of underlying type
    acceptString(nameInlineClass) // Not OK: can't pass inline class instead of underlying type

    // And vice versa:
    acceptNameTypeAlias(string) // OK: pass underlying type instead of alias
    acceptNameInlineClass(string) // Not OK: can't pass underlying type instead of inline class
}
```

**Source:** _blog.mindorks.com_
### Q4: What is Coroutine Scope and how is that different from Coroutine Context? ☆☆☆☆

**Answer:**
* Coroutines always execute in some context represented by a value of the **CoroutineContext** type, defined in the Kotlin standard library. The coroutine context is a set of various elements. The main elements are the **Job** of the coroutine.

* **CoroutineScope** has no data on its own, it just holds a **CoroutineContext**. Its key role is as the implicit receiver of the block you pass to `launch`, `async` etc.

 ```kotlin
runBlocking {
    val scope0 = this
    // scope0 is the top-level coroutine scope.
    scope0.launch {
        val scope1 = this
        // scope1 inherits its context from scope0. It replaces the Job field
        // with its own job, which is a child of the job in scope0.
        // It retains the Dispatcher field so the launched coroutine uses
        // the dispatcher created by runBlocking.
        scope1.launch {
            val scope2 = this
            // scope2 inherits from scope1
        }
    }
}
```
You might say that **CoroutineScope** formalizes the way the **CoroutineContext** is inherited. You can see how the **CoroutineScope** mediates the inheritance of coroutine contexts. If you cancel the job in `scope1`, this will propagate to `scope2` and will cancel the launched job as well.


**Source:** _stackoverflow.com_
### Q5: Imagine you moving your code from Java to Kotlin. How would you rewrite this code in Kotlin? ☆☆☆☆☆

**Details:**
```java
public class Foo {
    private static final Logger LOG = LoggerFactory.getLogger(Foo.class);
}
```

**Answer:**
Use **Static-like** approach:

```kotlin
class MyClass {
    companion object {
        val LOG = Logger.getLogger(MyClass::class.java.name) 
    }

    fun foo() {
        LOG.warning("Hello from MyClass")
    }
}  
```

**Source:** _stackoverflow.com_
### Q6: How would you override default getter for Kotlin data class? ☆☆☆☆

**Details:**
Given the following Kotlin class:
```kotlin
data class Test(val value: Int)
```
How would I override the Int getter so that it returns `0` if the value negative?

**Answer:**
1. Have your business logic that creates the data class alter the value to be 0 or greater before calling the constructor with the bad value. This is probably the best approach for most cases.
2. Don't use a `data class`. Use a regular `class`.
 ```kotlin
 class Test(value: Int) {
    val value: Int = value
     get() = if (field < 0) 0 else field
 
     override fun equals(other: Any?): Boolean {
      if (this === other) return true
      if (other !is Test) return false
      return true
    }
 
    override fun hashCode(): Int {
      return javaClass.hashCode()
    }
 }
 ```
3. Create an additional safe property on the object that does what you want instead of having a private value that's effectively overriden.
 ```kotlin
 data class Test(val value: Int) {
   val safeValue: Int
     get() = if (value < 0) 0 else value
 }
 ```

**Source:** _stackoverflow.com_
### Q7: What is Kotlin backing field is used for? ☆☆☆☆

**Answer:**
Backing field is an autogenerated field for any property which can only be used inside the accessors(getter or setter) and will be present only if it uses the default implementation of at least one of the accessors, or if a custom accessor references it through the `field` identifier. _This backing field is used to avoid the recursive call of an accessor which ultimately prevents the StackOverflowError._

Classes in Kotlin cannot have **fields**. However, sometimes it is necessary to have a backing field when using custom accessors. For these purposes, Kotlin provides an automatic backing field which can be accessed using the field identifier.

```kotlin
var selectedColor: Int = someDefaultValue
        get() = field
        set(value) {
            field = value
        }
```

**Source:** _stackoverflow.com_
### Q8: What are Object expressions in Kotlin and when to use them? ☆☆☆☆

**Answer:**
Sometimes we need to create an object of some class with slight modification, without explicitly declaring a new subclass for it. Java handles this case with anonymous inner classes. Kotlin uses **object expression** to achieve the same functionality. We can even create an object expression for an interface or abstract class by just implementing their abstract methods.

It is often used as a substitution to a Java anonymous class:

```kotlin
window.addMouseListener(object : MouseAdapter() {
    override fun mouseClicked(e: MouseEvent) {
        // ...
    }

    override fun mouseEntered(e: MouseEvent) {
        // ...
    }
})
```

**Source:** _kotlinlang.org_
### Q9: How to create empty constructor for data class in Kotlin? ☆☆☆☆

**Answer:**
If you give **default values to all the fields** - empty constructor is generated automatically by Kotlin.

```kotlin
data class User(var id: Long = -1,
               var uniqueIdentifier: String? = null)
```

and you can simply call:

```kotlin
val user = User()
```

Another option is to declare a secondary constructor that has no parameters:
```kotlin
data class User(var id: Long,
               var uniqueIdentifier: String?){
    constructor() : this(-1, null)
}
```

**Source:** _stackoverflow.com_
### Q10: How to create an instance of anonymous class of abstract class in Kotlin? ☆☆☆☆

**Details:**
Assume that `KeyAdapter` is an abstract class with several methods that can be overridden.

In java I can do:
```kotlin
KeyListener keyListener = new KeyAdapter() {
    @Override public void keyPressed(KeyEvent keyEvent) {
        // ...
    }
};
```
How to do the same in Kotlin?

**Answer:**
Sometimes we need to create an object of a slight modification of some class, without explicitly declaring a new subclass for it. Kotlin handles this case with _object expressions_ and _object declarations_.

```kotlin
val keyListener = object : KeyAdapter() { 
    override fun keyPressed(keyEvent : KeyEvent) { 
    // ... 
} 
```

**Source:** _stackoverflow.com_
### Q11: Why do we use “companion object” as a kind of replacement for Java static fields in Kotlin? ☆☆☆☆☆

**Answer:**
Because `static`s are not object-oriented. Kotlin does, however, have globals, which function similarly, and objects, which provide static functionality but remain object-oriented.

Java `static` part of a class can be elegantly expressed in terms of singleton: it's a singleton object that can be called by the class' name. Hence the naming: it's an object that comes with a class.

Apart from naming, it is more powerful than Java static members: it can extend classes and interfaces, and you can reference and pass it around just like other objects.

**Source:** _stackoverflow.com_
### Q12: What is the difference between “*” and “Any” in Kotlin generics? ☆☆☆☆☆

**Answer:**
* `List<*>` can contain objects of any type, but _only that type_, so it can contain `Strings` (but only `Strings`)
* while `List<Any>` can contain `Strings` and `Integers` and whatnot, all in the same list

**Source:** _stackoverflow.com_
### Q13: How can I create “static” method for enum in Kotiln? ☆☆☆☆

**Answer:**
Just like with any other class, you can define a class object in an enum class:

```kotlin
enum class CircleType {
  FIRST,
  SECOND,
  THIRD;
  companion object {
     fun random(): CircleType = FIRST
  }
}
```
Then you'll be able to call this function as `CircleType.random()`.

**Source:** _stackoverflow.com_
### Q14: What is SAM Conversion in Kotlin? ☆☆☆☆☆

**Answer:**
 "SAM" stands for "single abstract method", and "SAM-type" refers to interfaces like Runnable, Callable.

Just like Java 8, Kotlin supports SAM conversions. This means that Kotlin function literals can be automatically converted into implementations of Java interfaces with a single non-default method, as long as the parameter types of the interface method match the parameter types of the Kotlin function.

That means that when you call some Java method from Kotlin, and that method satisfies conditions described above, you can pass lambda or method reference instead.

**Source:** _kotlinlang.org_
### Q15: Explain the difference between lateinit and lazy in details ☆☆☆☆☆

**Answer:**
Here are the significant differences between `lateinit var` and `by lazy { ... }` delegated property:

* `lazy { ... }` delegate can only be used for `val` properties, whereas `lateinit` can only be applied to `var`s, because it can't be compiled to a `final` field, thus no immutability can be guaranteed;

* `lateinit var` has a backing field which stores the value, and `by lazy { ... }` creates a delegate object in which the value is stored once calculated, stores the reference to the delegate instance in the class object and generates the getter for the property that works with the delegate instance. So if you need the backing field present in the class, use `lateinit`;

* In addition to `val`s, `lateinit` cannot be used for nullable properties and Java primitive types (this is because of `null` used for uninitialized value);

* `lateinit var` can be initialized from anywhere the object is seen from, e.g. from inside a framework code, and multiple initialization scenarios are possible for different objects of a single class. `by lazy { ... }`, in turn, defines the only initializer for the property, which can be altered only by overriding the property in a subclass. If you want your property to be initialized from outside in a way probably unknown beforehand, use `lateinit`.

* Initialization `by lazy { ... }` is thread-safe by default and guarantees that the initializer is invoked at most once (but this can be altered by using [another `lazy` overload][1]). In the case of `lateinit var`, it's up to the user's code to initialize the property correctly in multi-threaded environments.

* A `Lazy` instance can be saved, passed around and even used for multiple properties. On contrary, `lateinit var`s do not store any additional runtime state (only `null` in the field for uninitialized value).

* If you hold a reference to an instance of `Lazy`, [`isInitialized()`][2] allows you to check whether it has already been initialized (and you can [obtain such instance with reflection][3] from a delegated property). To check whether a lateinit property has been initialized, you can [use `property::isInitialized` since Kotlin 1.2][4].

* A lambda passed to `by lazy { ... }` may capture references from the context where it is used into its [closure][5].. It will then store the references and release them only once the property has been initialized. This may lead to object hierarchies, such as Android activities, not being released for too long (or ever, if the property remains accessible and is never accessed), so you should be careful about what you use inside the initializer lambda.

**Source:** _stackoverflow.com_
### Q16: Provide a real use case when inline classes may be useful ☆☆☆☆

**Answer:**
Imagine an authentication method in an API that looks as follows:

```kotlin
fun auth(userName: String, password: String) { println("authenticating $userName.") }
```
Since both parameters are of type String, you may mess up their order which gets even more likely with an increasing number of arguments.

Inline class wrappers around these types can help you mitigate that risk and give you simple, type-safe wrappers without introducing additional heap allocations:

```kotlin
inline class Password(val value: String)
inline class UserName(val value: String)

fun auth(userName: UserName, password: Password) { println("authenticating $userName.")}

fun main() {
    auth(UserName("user1"), Password("12345"))
    //does not compile due to type mismatch
    auth(Password("12345"), UserName("user1"))
}
```

**Source:** _kotlinexpertise.com_
### Q17: What's wrong with that code? ☆☆☆☆☆

**Details:**
Let's say I want to override the Int getter so that it returns 0 if the value negative for the data class. What's bad with that approach?

```kotlin
data class Test(private val _value: Int) {
  val value: Int
    get() = if (_value < 0) 0 else _value
}
```

**Answer:**
The problem with this approach is that data classes aren't really meant for altering data like this. They are really just for _holding_ data. Overriding the getter for a data class like this would mean that `Test(0)` and `Test(-1)` wouldn't equal one another and would have different `hashCodes`, but when you called `.value`, they would have the same result. This is inconsistent, and while it may work for you, other people on your team who see this is a data class, may accidentally misuse it.

**Source:** _stackoverflow.com_
### Q18: Why would you use apply in Kotlin? ☆☆☆

**Answer:**
Look at this code:

```kotlin
person.name = "Tony Stark"
person.age = 52
```

and equivalent with apply will be:
```kotlin
val person = Person().apply {
    name = "Tony Stark" // this. can be omitted
    age = 52 // this. can be omitted
    // ...
}
```
This way you don't have to repeat person several times. Apply is used to keep things that belong together in one place (mostly initializations).

**Source:** _stackoverflow.com_
### Q19: Rewrite this code using "run" extension function  ☆☆☆☆

**Details:**
Consider:
```kotlin
val generator = PasswordGenerator()
generator.seed = "someString"
generator.hash = {s -> someHash(s)}
generator.hashRepititions = 1000

val password: Password = generator.generate()
```
How would you refactor this code using `run` extension function?

**Answer:**
Someone didn’t quite think through the design of this password generator class. Its constructor does nothing, but it needs a lot of initialization. To use this class, I need to introduce a variable generator, set all necessary parameters and use `generate` to generate the actual password. 

```kotlin
val password: Password = PasswordGenerator().run {
       seed = "someString"
       hash = {s -> someHash(s)}
       hashRepetitions = 1000

       generate()
}
```
Lambdas in Kotlin implicitly return the result of the last line. That’s why I can omit the temporary variable and store the password directly. Because an extension function is passed to `run` I can also access the password generator’s properties like `seed` or `hash` directly.

**Source:** _stackoverflow.com_
### Q20: How would you refactor this code using "apply"? ☆☆☆

**Details:**
Consider:
```kotlin
class Message(message: String, signature: String) {
  val body = MessageBody()
  
  init {
    body.text = message + "\n" + signature
  }
}
```
Do you see any refactoring that could be done?

**Answer:**
You can write:
```kotlin
class Message(message: String, signature: String) {
  val body = MessageBody().apply {
    text = message + "\n" + signature
  }
}
```

**Source:** _cargocult.dev_

### Q1: What is The Billion Dollar Mistake? ☆☆☆☆☆

**Answer:**
Kotlin's type system is aimed at eliminating the danger of null references from code, also known as the The Billion Dollar Mistake.

One of the most common pitfalls in many programming languages, including Java, is that accessing a member of a null reference will result in a null reference exception. In Kotlin, the type system distinguishes between references that can hold null (nullable references) and those that can not (non-null references).

_I call it my billion-dollar mistake. It was the invention of the **null reference** in 1965. At that time, I was designing the first comprehensive type system for references in an object-oriented language (ALGOL W). My goal was to ensure that all use of references should be absolutely safe, with checking performed automatically by the compiler. But I couldn’t resist the temptation to put in a null reference, simply because it was so easy to implement. This has led to innumerable errors, vulnerabilities, and system crashes, which have probably caused a billion dollars of pain and damage in the last forty years._

Tony Hoare at QCon London in 2009 https://en.wikipedia.org/wiki/Tony_Hoare

**Source:** _kotlinlang.org_
### Q2: What is a motivation to make classes final by default in Kotlin? Do you agree with that decision? ☆☆☆☆☆

**Answer:**
* First Kotlin takes many ideas from the functional programming world and uses immutability as often as it can to avoid all the known problems with mutation. Also proper designing a class for inheritance requires an excruciating amount of work (and building at least 3 separate subclasses, to verify that you base class actually is useful). Most classes should be final. Extending them is probably a bad idea.

* The second thought which comes to my mind is that inheritance is often missused. There is the principle "Favor composition over inheritance" as a guideline for better designs. So declaring every class as final by default forces the developer to at least stop for a moment and think about alternative ways to solve the problem instead of using inheritance for the wrong reasons.

**Source:** _stackoverflow.com_
### Q3: How does the reified keyword in Kotlin work? ☆☆☆☆☆

**Answer:**
In an ordinary generic function like `myGenericFun`, you can't access the type `T` because it is, like in Java, erased at runtime and thus only available at compile time. Therefore, if you want to use the generic type as a normal `Class` in the function body you need to explicitly pass the class as a parameter like the parameter `c` in the example. 

```kotlin
fun <T> myGenericFun(c: Class<T>)
```
By marking a type as `reified`, we’ll have the ability to use that type within the function.

As for a real example, in Java, when we call `startActivity`, we need to specify the destination class as a parameter. The Kotlin way is:
```kotlin
inline fun <reified T : Activity> Activity.startActivity() {
    startActivity(Intent(this, T::class.java))
}
```

You can only use `reified` in combination with an _inline function_. Such a function makes the compiler _copy the function's bytecode to every place where the function is being used_ (the function is being "inlined"). When you call an inline function with reified type, the _compiler knows_ the actual type used as a type argument and modifies the generated bytecode to use the corresponding class directly. Therefore calls like `myVar is T` become `myVar is String` (if the type argument were `String`) in the bytecode and at runtime.

**Source:** _stackoverflow.com_
### Q4: How to implement Builder pattern in Kotlin? ☆☆☆☆☆

**Answer:**
First and foremost, in most cases you don't need to use builders in Kotlin because we have default and named arguments but if you need one use:

```kotlin
class Car( //add private constructor if necessary
        val model: String?,
        val year: Int
) {

    private constructor(builder: Builder) : this(builder.model, builder.year)

    class Builder {
        var model: String? = null
            private set

        var year: Int = 0
            private set

        fun model(model: String) = apply { this.model = model }

        fun year(year: Int) = apply { this.year = year }

        fun build() = Car(this)
    }
}
```
Usage:
```kotlin
val car = Car.Builder().model("X").build()
```

**Source:** _stackoverflow.com_
### Q5: When to use and do not use an inline function in Kotlin? ☆☆☆☆☆

**Answer:**
Using higher-order functions imposes certain runtime penalties: each function is an object, and it captures a closure, i.e. those variables that are accessed in the body of the function. Memory allocations (both for function objects and classes) and virtual calls introduce runtime overhead.

But it appears that in many cases this kind of overhead can be eliminated by _inlining the lambda expressions_. 

The `inline` modifier affects both the function itself and the lambdas passed to it: all of those will be inlined into the call site.

The most important case when we use inline modifier is when we define util-like functions with parameter functions. This is why inline modifier is mostly an important optimization for library developers. 

Consider:
```kotlin
inline fun inlined(block: () -> Unit) {
    println("before")
    block()
    println("after")
}

inlined {
    println("do something here")
}

// No Function object instance will be created, instead, the code around the 
// invocation of block inside the inlined function will be copied 
// to the call site
System.out.println("before");
System.out.println("do something here");
System.out.println("after");
```

When we don’t have function type parameter, reified type parameter, and we don’t need non-local return, then we most likely shouldn’t use inline modifier. 

Also there is the code size problem. Inlining a large function could dramatically increase the size of the bytecode because it's copied to every calls site. Inlining may cause the generated code to grow; however, if we do it in a reasonable way (i.e. avoiding inlining large functions), it will pay off in performance.

**Source:** _stackoverflow.com_
### Q6: How Kotlin coroutines are better than RxKotlin/RxJava? ☆☆☆☆☆

**Answer:**
Kotlin coroutines are different from Rx. Both are designed to address a problem of asynchronous programming, however their approach to solution is very different:

* Rx comes with a particular functional style of programming that can be implemented in virtually any programming language without support from the language itself. It works well when the problem at hand easily decomposes into a sequence of standard operators and not so well otherwise.

* Kotlin coroutines provide a language feature that let library writers implement various asynchronous programming styles, including, but not limited to functional reactive style (Rx). With Kotlin coroutines you can also write your asynchronous code in imperative style, in promise/futures-based style, in actor-style, etc.

How Kotlin coroutines are better than RxKotlin? You just write sequential code, everything is as easy as writing synchronous code except it execute asynchronously. It's easier to grasp.

Coroutines are better to deal with resources

 - In RxJava you can assign computations to schedulers but `subscribeOn()` and `ObserveOn()`are confusing. Every coroutine is given a thread context and return to parent context. For a channel, both side (producer, consumer) execute on his own context. Coroutines are more intuitive on thread or thread pool affectation. 
 - Coroutines give more control on when those computation occur. You can for example pass hand (`yield`), prioritize (`select`), parallelize (multiple `producer`/`actor` on `channel`) or lock resource (`Mutex`) for a given computation. It may not matter on server (where RxJava came first) but on resources limited environment this level of control may be required.
 - Due to it's reactive nature, backpressure doesn't fit well in RxJava. In the other end `send()` to channel is a suspensive function that suspend when channel capacity is reached. It's out-of-the-box backpressure given by nature. You could also `offer()` to channel, in which case the call never suspend but return `false` in case the channel is full, effectively reproducing `onBackpressureDrop()` from RxJava. Or you could just write your own custom backpressure logic, which won't be difficult with coroutines, especially compared to do the same with RxJava.


**Source:** _stackoverflow.com_
### Q7: What is the difference between launch/join and async/await in Kotlin coroutines? ☆☆☆☆☆

**Answer:**
* **launch** is used to** fire and forget coroutine**. It is like starting a new thread. If the code inside the `launch` terminates with exception, then it is treated like _uncaught_ exception in a thread -- usually printed to stderr in backend JVM applications and crashes Android applications. `join` is used to wait for completion of the launched coroutine and it does not propagate its exception. However, a crashed _child_ coroutine cancels its parent with the corresponding exception, too.

* **async** is used to **start a coroutine that computes some result**. The result is represented by an instance of `Deferred` and you **must** use `await` on it. An uncaught exception inside the async code is stored inside the resulting `Deferred` and is not delivered anywhere else, it will get silently dropped unless processed. **You MUST NOT forget about the coroutine you’ve started with async.**

**Source:** _stackoverflow.com_
### Q68: What is the difference between Java field and Kotlin property? ☆☆☆☆☆

**Answer:**
This is an example of a Java field:
```java
public String name = "Marcin";
```
Here is an example of a Kotlin property:
```kotlin
var name: String = "Marcin"
```
They both look very similar, but these are two different concepts. Direct Java equivalent of above Kotlin property is following:
```java
private String name = "Marcin";
public String getName() {
    return name;
}
public void setName(String name) {
    this.name = name;
}
```
The default implementation of Kotlin property includes field and accessors (getter for val, and getter and setter for var). Thanks to that, we can always replace accessors default implementation with a custom one.

**Source:** _blog.kotlin-academy.com_
### Q69: What is the difference between and interface and an abstract class? ☆☆

**Answer:**
Though both may seem very similar they are in fact very different and serve very different purposes. Abstract classes are meant to serve the purpose of Generalizing behavior while interfaces are meant to serve the purpose of Standardizing behavior.

**Source:** _paulfran.co/_