//
// Created by Administrator on 2021/6/20.
//

#ifndef ALGORITHM_VECTOR_H
#define ALGORITHM_VECTOR_H

#include <iostream>

template<typename T>
class Vector;

template<typename T>
class VectorNode {
private:
    T element;
    VectorNode<T> *next;

    friend class Vector<T>;
};


template<typename T>
class Vector {
private:
    VectorNode<T> *head;
public:
    Vector();

    ~Vector();

public:
    class Iterator {

    };

public:
    bool isEmpty() const;

    const T &front() const;

    void add(const T &t);

    void remove();

    void reserve();

    void print();
};


#endif //ALGORITHM_VECTOR_H