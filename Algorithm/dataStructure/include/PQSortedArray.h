#ifndef DATASTRUCTURE_PQSORTEDARRAY_H
#define DATASTRUCTURE_PQSORTEDARRAY_H

#include <tuple>

template<class T>
class PQSortedArray {
public:
    explicit PQSortedArray(const int &maxSize = 1000) {
        sortedArray = new std::tuple<T, int>[maxSize];
        maxArrSize = maxSize;
        arrSize = 0;
    }

public:
    T top() {
        if (arrSize <= 0) {
            return T(); //...
        }
        return std::get<0>(sortedArray[arrSize - 1]);
    }

    T peek() {
        if (arrSize <= 0) {
            return T();
        }
        T result = std::get<0>(sortedArray[arrSize - 1]);
        arrSize -= 1;
        // sortedArray[arrSize] = std::tuple<T, int>(T(), 0);
        return result;
    }

    int insert(T element, int priority) {
        if (arrSize >= maxArrSize) {
            return -1;
        }
        int insertIdx;
        for (int i = arrSize - 1; i >= 0; i--) {
            auto ele = sortedArray[i];
            if (std::get<1>(ele) < priority) {
                insertIdx = i;
                break;
            }
        }
        for (int i = arrSize; i > insertIdx; i--) {
            sortedArray[i] = sortedArray[i - 1];
        }
        sortedArray[insertIdx] = std::tuple<T, int>(element, priority);

        return insertIdx;
    }

    int update(T element, int priority) {
        remove(element);
        return insert(element, priority);
    }

    int remove(T element) {
        int eleIdx;
        for (int i = 0; i < arrSize; i++) {
            if (std::get<0>(sortedArray[i]) == element) {
                eleIdx = i;
                break;
            }
        }
        for (int j = eleIdx; j < arrSize - 1; j++) {
            sortedArray[j] = sortedArray[j + 1];
        }
        arrSize -= 1;
        return eleIdx;
    }

    inline bool isEmpty() { return arrSize <= 0; };
private:
    std::tuple<T, int> *sortedArray;
    int arrSize{};
    int maxArrSize{};
};

#endif //DATASTRUCTURE_PQSORTEDARRAY_H
