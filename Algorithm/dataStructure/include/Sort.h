// https://en.wikipedia.org/wiki/Sorting_algorithm

#ifndef DATASTRUCTURE_SORT_H
#define DATASTRUCTURE_SORT_H

// Comparison Sorting. Comparison Sorting cannot perform better than O(n * log(n)) in average.
template<class T>
void sort_quick(T* begin, T* end);

#include "../src/Sort.cpp"

#endif //DATASTRUCTURE_SORT_H
