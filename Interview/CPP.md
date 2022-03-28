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

## difference between reference and point.

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