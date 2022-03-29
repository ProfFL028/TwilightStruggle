#include "PQUnsortedArray.h"
#include <iostream>

template<class T>
PQUnsortedArray<T>::PQUnsortedArray(int maxSize) {
    unsortedArray = new std::tuple<T *, int>[maxSize];
    arrSize = 0;
    maxArrSize = maxSize;
    nextIdx = -1;
}

template<class T>
PQUnsortedArray<T>::~PQUnsortedArray<T>() {
    delete[] unsortedArray;
}

template<class T>
T *PQUnsortedArray<T>::top() {
    // check if the queue has element.
    if (arrSize > 0) {
        return std::get<0>(unsortedArray[nextIdx]);
    } else {
        return nullptr;
    }
}

template<class T>
T *PQUnsortedArray<T>::peek() {
    // return nullptr if there's no element in the queue.
    if (arrSize <= 0) {
        return nullptr;
    }
    // move elements.
    auto result = unsortedArray[nextIdx];
    forward(nextIdx);

    updateIdx();

    return std::get<0>(result);
}

template<class T>
int PQUnsortedArray<T>::insert(T *element, int priority) {
    if (arrSize > maxArrSize) {
        return -1;
    }
    // add the element at the end.
    unsortedArray[arrSize++] = std::tuple<T *, int>(element, priority);
    // update nextIdx if needed.
    if (std::get<1>(unsortedArray[nextIdx]) < priority) {
        nextIdx = arrSize - 1;
    }
    return arrSize - 1;
}

template<class T>
int PQUnsortedArray<T>::remove(T *element) {
    int eleIdx = -1;
    for (int i = 0; i < arrSize; i++) {
        if (std::get<0>(unsortedArray[i]) == element) {
            eleIdx = i;
            break;
        }
    }
    if (eleIdx >= 0) {
        if (eleIdx == nextIdx) {
            peek();
        } else {
            forward();
        }
    }
    return eleIdx;
}

template<class T>
void PQUnsortedArray<T>::forward(int beginIdx) {
    for (int i = beginIdx; i < arrSize - 1; i++) {
        unsortedArray[i] = unsortedArray[i + 1];
    }
    // delete last element.
    std::get<0>(unsortedArray[arrSize - 1]) = nullptr;
    std::get<1>(unsortedArray[arrSize - 1]) = 0;
    arrSize -= 1;
}

template<class T>
int PQUnsortedArray<T>::update(T *element, int newPriority) {
    int eleIdx = -1;
    for (int i = 0; i < arrSize; i++) {
        if (std::get<0>(unsortedArray[i]) == element) {
            eleIdx = i;
            break;
        }
    }
    int oldPriority = std::get<1>(unsortedArray[eleIdx]);
    std::get<1>(unsortedArray[eleIdx]) = newPriority;
    if ((eleIdx == nextIdx && oldPriority > newPriority) || (eleIdx != nextIdx && oldPriority < newPriority)) {
        updateIdx();
    }
}

template<class T>
void PQUnsortedArray<T>::updateIdx() {
    // get next element in the queue.
    int maxPriority = -1;
    for (int i = 0; i < arrSize; i++) {
        auto ele = unsortedArray[i];
        if (std::get<1>(ele) > maxPriority) {
            maxPriority = std::get<1>(ele);
            nextIdx = i;
        }
    }
}
