// https://en.wikipedia.org/wiki/Sorting_algorithm

#ifndef DATASTRUCTURE_SORT_H
#define DATASTRUCTURE_SORT_H

#include <iostream>
#include <Vector.h>

namespace sort {
#define SWAP(a, b, size)  \
 do {                     \
    size_t __size = size;    \
    char *__a=(a), *__b=(b); \
    while (__size > 0) {     \
        char* __tmp = *__a;  \
        *__a++ = *__b;       \
        *__b++ = tmp;        \
        __size--;            \
    }                    \
  } while(0)              \

    struct {
        char *leftIdx;
        char *rightIdx;
    } StackNode;
/**
 * CHAR_BIT: how many bits to represent a char.
 * sizeof(size_t): 8.
 * A fast inline stack abstractions. Usage:
 * StackNode stack[STACK_SIZE]; // using a array of size STACK_SIZE to represent the stack where the stack's name should be stack.
 * StackNode* top = stack; // reference to the first node.
 * PUSH(left, right);
 * while (STACK_NOT_EMPTY) doSomething
 */
#define STACK_SIZE (CHAR_BIT * sizeof(size_t))
#define PUSH(left, right) ((void) ((top->leftIdx=left), (top->rightIdx=right)), ++top)
#define POP(left, right) ((void) (--top, (left=top->leftIdx), (right=top->rightIdx)))
#define STACK_NOT_EMPTY (stack < top)

// Comparison Sorting functions. Comparison Sorting cannot perform better than O(n * log(n)) in average.

/**
 * quick sort modify from https://code.woboq.org/userspace/glibc/stdlib/qsort.c.html#4cmp
 * The following method will speed up quick sort ff we know the array size and all the elements are arranged in sequence memories.
 * 1. Non-recursive. Using a stack to store partition regions.
 * 2. Eliminates extraneous comparisons. Sort the first, middle and last three element in the array using given comparison function. And choose the middle element to partition the array into two separate parts.
 * 3. Only quick sort TOTAL_ELEMENTS/MAX_THRESH partitions. Leaving insert sorting to order the MAX_THRESH elements within each partitions.
 * 4. The larger of the two sub partitions is always pushed onto the stack first, with the algorithm concentrating on the smaller partition.
 */
    template<class T>
    void sort_quick(T *begin, T *end, int size) {
        static const int MAX_THRESH = 4;
    }

    template<class T>
    void sort_quick_vector(ds::Vector<T>& vector) {

    }

    template<class T>
    void sort_quick_recursive(ds::Vector<T> &vector) {
        if (vector.length <= 1)
            return;
        if (vector.length == 2) {
            if (vector.head->element > vector.head->next->element) {
                std::swap(vector.head->element, vector.head->next->element);
            }
            return ;
        }
        ds::Vector<T> left, right;
        T pivot = vector.head->element;
        auto it = vector.head->next;
        while (it != nullptr) {
            if (it->element > pivot) {
                right.insert(it->element);
            } else {
                left.insert(it->element);
            }
            it = it->next;
        }
        sort_quick_recursive(left);
        sort_quick_recursive(right);
        vector = left;
        vector.insert(pivot);
        vector.append(right);
    }

}
#endif //DATASTRUCTURE_SORT_H
