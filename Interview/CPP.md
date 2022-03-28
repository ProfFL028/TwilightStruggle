# CPP

## virutal function
A virtual function is a member function defined in  a base class and will be redefind in a derived class. If you point or reference to a derived class, it will call derived class's virtual function instead of base class's version.

* Virtual function cannot be static
* A class may have virtual deconstructor but it cannot have virtual constructor.

## pure virtual function
We do not need to write any function definition and only we have to declare it.
Add `=0` before `;`

## virtual constructor
In cpp, constructor cannot be virtual, because it is a statically typed language. So it is meanless to the compiler to create an object polymorphically. The compiler must aware the type of the object for creating it. In fact, only `inline` keywords can be added to constructor.

It is allowed to call virtual function in constructor, but it will never call derived function. virtual functions are not virtual in constructor function.

If you wanna to create a object without knowing exactly it's type, you can implement a virtual copy function.


## different between array and list.
An array is contiguous chuck of memory with a fixed size whereas  a list is typically implemented as individual elements linked to each other by pointers and does not have fixed size.
Once after an array is initialized, it uses a fixed size of memory space regardless of how much you accury use. Compared with list, you need to allocate memory dynamically and when you want put something in it, you require the os to allocate new spaces for the stuff and link to it.

Baically, we need only O(1) time to retrieve or modify an array element. But we need O(n) time when it comes to list. The advantage of using list instead of array is that list can save memory.

## difference between reference and pointer.
References are used to refer to an existing virable in another name whereas pointers are used to store the address of a virable.

References are not allowed to have null value but pointer can. And references must be initialized when declared, but pointer needn't.

A reference can be referenced by pass by value while a pointer can be referenced by pass by reference.

A reference shares the same memory address with the original variable but takes up some space on the stack. While a pointer has its own memory address and size on the stack.


## How to design a compiler, and how to arrange follow memory?
```cpp
class A {
    virtual void g();
    virtual void h();
    int mA;
};
class B {
    virtual void g();
    virtual void i();
    int mB;
}
```

## tr-catch-finally

## access priviledge differences.

## difference between abstract class and interface.