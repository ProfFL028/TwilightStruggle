#include "PQUnsortedArray.h"

template<class T>
PQUnsortedArray<T>::PQUnsortedArray(int maxSize) {
    unsortedArray = new std::tuple<T, int>[maxSize];
    arrSize = 0;
    maxArrSize = maxSize;
    nextIdx = 0;
}
template<class T>
PQUnsortedArray<T>::~PQUnsortedArray<T>() {
    delete [] unsortedArray;
}

template<class T>
T PQUnsortedArray<T>::top() {
    if (nextIdx >)
    return std::get<0>(unsortedArray[nextIdx]);
}

template<class T>
T PQUnsortedArray<T>::peek() {
    for (int i = 0; i < arrSize; i++) {

    }
    arrSize -= 1;
}


//T peek();
//void insert(T element, int priority);
//void remove(T element);
//void update(T element, int newPriority);
//
