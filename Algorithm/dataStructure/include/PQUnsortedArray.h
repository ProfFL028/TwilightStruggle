
#ifndef DATASTRUCTURE_PRIORITYQUUE_H
#define DATASTRUCTURE_PRIORITYQUUE_H

#include <tuple>

template<class T>
class PQUnsortedArray {
public:
    PQUnsortedArray(int maxSize=100);
    ~PQUnsortedArray();
public:
    T* top();
    T* peek();
    int insert(T* element, int priority);
    int remove(T* element);
    int update(T* element, int newPriority);

private:
    void forward(int beginIdx);
    void updateIdx();

private:
    std::tuple<T*, int>* unsortedArray;
    int arrSize;
    int maxArrSize;

    int nextIdx; // keep track of the last element. It makes top() method be O(1) in time.
};

#endif //DATASTRUCTURE_PRIORITYQUUE_H
