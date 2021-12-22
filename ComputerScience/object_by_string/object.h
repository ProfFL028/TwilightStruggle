#ifndef TINYTENSOR_OBJECT_H
#define TINYTENSOR_OBJECT_H

#include <iostream>
#include <map>
#include <unordered_map>

#define IMPLEMENT_CLASS(name) \
    static Object* createObject() { return new name; };

class Object {

public:
    Object();
    virtual ~Object() {};

    Object* createObject() { return new Object(); };
};

typedef Object* (*ObjectConstructorFn)(void);
class ObjectInfo {
public:
    static std::map< std::string, ObjectConstructorFn > nameConstructorMap;

public:
    static Object* forName(const std::string objectName);
    static bool regist(const std::string objectName, ObjectConstructorFn constructorFn);

};

class A : public Object {
public:
    IMPLEMENT_CLASS(A)
public:
    A() { std::cout << "A is created!" << std::endl; }
    ~A() { std::cout << "A is deleted!" << std::endl; }

};


#endif