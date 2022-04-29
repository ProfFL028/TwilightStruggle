
#ifndef DATASTRUCTURE_DARYHEAP_HPP
#define DATASTRUCTURE_DARYHEAP_HPP

#include <tuple>

template<class T, int D = 3>
class DAryHeap {
public:
    DAryHeap() {
        elements = new std::tuple<T, int>[curMaxSize];
    }

    virtual ~DAryHeap() {
        delete[]  elements;
    }

    void heapify(std::tuple<T, int> *arr, int sz) {
        this->elements = arr;
        this->len = sz;
        for (int i = sz - 1; i >= 0; i--) {
            bubbleDown(i);
        }
    }

public:
    T top() {
        if (len == 0) return T();
        if (len == 1) {
            len = 0;
            return elements[0].get(0);
        }
        auto first = elements[0];
        elements[0] = elements[--len];
        bubbleDown();
        return first.get(0);
    }

    T peek() {
        if (len == 0) return T();
        return elements[0].get(0);
    }

    void insert(const T &element, const int &priority) {
        std::tuple<T, int> newEle(element, priority);
        elements[len++] = newEle;
        bubbleUp(len - 1);
    }

    void update(T t, int newPriority) {
        int idx = find(t);
        if (idx >= 0) {
            int oldPriority = elements[t].get(1);
            if (newPriority > oldPriority) {
                bubbleUp(idx);
            } else {
                bubbleDown(idx);
            }
        }
    }

private: // some helper functions.
    void bubbleUp(int idx) {
        auto cur = elements[idx];
        while (idx > 0) {
            int parentIdx = getParentIndex(idx);
            if (elements[parentIdx].get(1) < cur.get(1)) {
                elements[idx] = elements[parentIdx];
                idx = parentIdx;
            } else {
                break;
            }
        }
        elements[idx] = cur;
    }

    void bubbleDown(int idx = 0) {
        auto cur = elements[idx];
        int firstLeafIndex = 0;
        while (idx < firstLeafIndex) {
            int highestChild = getHighestPriorityChild(idx);
            if (elements[highestChild].get(1) > elements[cur].get(1)) {
                elements[idx] = elements[highestChild];
                idx = highestChild;
            } else {
                break;
            }
        }
        elements[idx] = cur;
    }

    int getParentIndex(int idx) {
        if (idx == 0) {
            return 0;
        }
        return (idx - 1) / D;
    }

    int getFirstLeafIndex() {
        if (len <= 1) {
            return 0;
        }
        return (len - 2) / D + 1;
    }

    int getHighestPriorityChild(int idx) {
        int highest = idx * D;
        for (int i = idx * D; i < idx * D + D; i++) {
            if (i >= len) break;
            if (elements[highest].get(1) < elements[i].get(1)) {
                highest = i;
            }
        }

        return highest;
    }

    int find(T t) {
        // TODO: store t in a hash.
        for (int i = 0; i < len; i++) {
            if (elements[i].get(1) == t) {
                return i;
            }
        }
        return -1;
    }

private:
    std::tuple<T, int> *elements;
    const int MAX_SIZE = 1000;
    int curMaxSize = MAX_SIZE;
    int len = 0;
};

#endif //DATASTRUCTURE_DARYHEAP_HPP
