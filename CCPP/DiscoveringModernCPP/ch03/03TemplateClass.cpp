#include <iostream>

template<typename T>
class MyVector {
public:
    explicit MyVector(std::size_t s) : mySize{s}, data{new T[mySize]} {}

    MyVector(const MyVector<T> &src) : mySize{src.mySize}, data{new T[mySize]} {
        std::copy(&src.data[0], &src.data[src.mySize], &data[0]);
    }

    std::size_t size() const {
        return mySize;
    }

    const T &operator[](const std::size_t &i) const {
        checkIndex(i);
        return data[i];
    }

private:
    void checkIndex(const std::size_t &i) const {
        if (mySize == 0 || i < 0 || i >= mySize) {
            throw std::exception();
        }
    }

private:
    std::size_t mySize;
    std::unique_ptr<T[]> data;
};

template<typename T, std::size_t N>
T sum(const T(&array)[N]) {
    T result(0);
    for (std::size_t i = 0; i < N; i++) {
        result += array[i];
    }
    return result;
}

template<typename T>
struct list_entry {
    list_entry(const T &value) : value{value}, next{nullptr} {}

    T value;
    list_entry<T> *next;
};

template<typename T>
struct list {
    list() : first{nullptr}, end{nullptr} {}
    ~list() {
        while (first) {
            auto tmp = first->next;
            delete first;
            first = tmp;
        }
    }

    void append(const T& value) {
        if (!first) {
            end = first = new list_entry<T>(value);
        } else {
            end->next = new list_entry<T>(value);
            end = end->next;
        }
    }

    list_entry<T> *first, *end;
};

int main() {
    int ai[] = {2, 4, 7};
    double ad[] = {2., 4.5, 7.};
    std::cout << "sum ai is " << sum(ai) << '\n';
    std::cout << "sum ad is " << sum(ad) << '\n';
    return 0;
}
