#include "Vector.h"
#include <iostream>

template<typename T>
Vector<T>::Vector(): head(NULL) {
}

template<typename T>
Vector<T>::~Vector() {
    while (!this->isEmpty()) this->remove();
}

template<typename T>
bool Vector<T>::isEmpty() const {
    return this->head == NULL;
}

template<typename T>
void Vector<T>::add(const T &t) {
    VectorNode<T> *node = new VectorNode<T>();
    node->element = t;
    node->next = this->head;
    this->head = node;
}

template<typename T>
void Vector<T>::print() {
    VectorNode<T>* cur = this->head;
    while (cur != NULL) {
        std::cout << cur->element;
        cur = cur->next;
    }
    std::cout << std::endl;
}

template<typename T>
void Vector<T>::remove() {
    VectorNode<T>* cur = this->head;
    this->head = cur->next;
    delete cur;
}

template<typename T>
void Vector<T>::reserve() {
    VectorNode<T>* cur = this->head;
    VectorNode<T>* prev = NULL;
    while (cur != NULL) {
        VectorNode<T>* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    this->head = prev;
}

template<typename T>
Iterator<T> Vector<T>::next() {
    
}