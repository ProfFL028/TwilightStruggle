
#ifndef DATASTRUCTURE_DARYHEAP_HPP
#define DATASTRUCTURE_DARYHEAP_HPP

template<class T, int D = 3>
class DAryHeap {
public:
    DAryHeap() {
        elements = new T[curMaxSize];
    }

    virtual ~DAryHeap() {
        delete[]  elements;
    }

public:
    T top();

    T peek();

    void insert(const T &element, const int &priority);

    void update();

private: // some helper functions.

private:
    T *elements;
    const int MAX_SIZE = 1000;
    int curMaxSize = MAX_SIZE;
    int len = 0;
};

#endif //DATASTRUCTURE_DARYHEAP_HPP
