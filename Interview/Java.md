# Java

## java garbage collector.

GC is used to perform automatic memory management. The programmer does not need to explicitly mark objects to be deleted.

## Java initialization process.
Java initialization process have three principles:

* Static members initialize before non-static members.
* Super class initialize before child class.
* Initialize members order by declare sequence.

[InitSeq](./JavaInterviewGuide/src/main/kotlin/me/proffl/ch01/SequenceOnInit.kt)

## Constructor
* Constructor must have the same name with class name.
* Everyclass has a constructor, and can have multiple constructors. If there's no constructor explicitly defined, the compiler will automatically generator a non-parameter empty constructor.
* Constructor cann't be <b>override</b> but can be <b>overload</b>.
* If super class has non-parameter constructor, child class will call this method automatic if child constructor doesn't call any super constructor. And if super class doesn't have non-parameter constructor, then child class has to call one of its parent constructor explicitly.

## Reflection
There's three ways for us to get an instance from `Class`:[ReflectionMethods](./JavaInterviewGuide/src/main/kotlin/me/proffl/ch01/ReflectionMethods.kt)
```kotlin
A::class.java
Class.forName("A")
A()::class::java
```

## Difference between override and overload
Overload refers to a class can have several methods that their names are the same, but have different parameters or parameter types or parameter sequence.<br>
But you can't overload through different return type, access privilege or throw different exceptions.<br>
It's import to notice that when parent class's method is `private`, write a method with same name and parameters is just another new method.

Override refers to a child class override its parent's method.<br/>
They must have the same name, parameters and return type.<br>
Child class must throw exception that is the same or child of the exception if parent class throws exception.

## volatile
volatile can help with `operator reorder problem` in multi thread programs, but it doesn't guarantee atomicity.
```kotlin
var i = 0
var f = false

val r1 = Runnable {
    while (!f) {
        println(i)
    }
}
val r2 = Runnable {
    Thread.sleep(1000)
    i++
    f = true
}
Thread(r1).start()
Thread(r2).start()
```

## Java IO

### Implement 

## difference between dom and sax.
