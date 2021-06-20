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
        std::cout << cur->element << std::endl;
        cur = cur->next;
    }

}