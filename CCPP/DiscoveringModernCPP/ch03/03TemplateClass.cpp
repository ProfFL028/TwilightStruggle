#include <iostream>

template<typename T>
class MyVector {
public:
    explicit MyVector(std::size_t s) : mySize{s}, data{new T[mySize]} {}

    MyVector(const MyVector<T> &src) : mySize{src.mySize}, data{new T[mySize]} {
        std::copy(&src.data[0], &src.data[src.mySize], &data[0]);
    }

    [[nodiscard]] std::size_t size() const {
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
    explicit list_entry(const T &value) : value{value}, next{nullptr} {}

    T value;
    list_entry<T> *next;
};


template<typename T>
struct list_iterator {
    using value_type = T;

    explicit list_iterator(list_entry<T> *e) : entry{e} {}

    T &operator*() { return entry->value; }

    const T &operator*() const { return entry->value; }

    list_iterator<T> &operator++() { // prefix
        entry = entry->next;
        return *this;
    }

    list_iterator<T> &operator++(int) {
        list_iterator<T> tmp(*this);
        entry = entry->next;
        return tmp;
    }

    bool operator!=(const list_iterator<T> &other) const {
        return entry != other.entry;
    }

    list_entry<T> *entry;
};


template<typename T>
struct list {
    list() : first{nullptr}, end{nullptr} {}

    explicit list(std::initializer_list<T> values) : first{nullptr}, end{nullptr} {
        for (auto v: values) {
            append(v);
        }
    }

    ~list() {
        while (first) {
            auto tmp = first->next;
            delete first;
            first = tmp;
        }
    }

    void append(const T &value) {
        if (!first) {
            first = new list_entry<T>(value);
            end = first;
        } else {
            end->next = new list_entry<T>(value);
            end = end->next;
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const list<T> &l) {
        auto x = l.first;
        out << "[";
        while (x != nullptr) {
            out << x->value << ", ";
            x = x->next;
        }
        out << "\b\b]";
        return out;
    }

    list_entry<T> *first, *end;

    list_iterator<T> begin() { return list_iterator<T>(first); }

    list_iterator<T> end2() { return list_iterator<T>(nullptr); }
};

template<typename T>
T sum(const list<T> &l) {
    T result(0);
    for (auto e = l.first; e != nullptr; e = e->next) {
        result += e->value;
    }
    return result;
}

template<typename Iter, typename T>
inline T acc_sum(Iter it, Iter end, T init) {
    for (; it != end; ++it) {
        init += *it;
    }
    return init;
}

int main() {
    int ai[] = {2, 4, 7};
    double ad[] = {2., 4.5, 7.};
    std::cout << "sum ai is " << sum(ai) << '\n';
    std::cout << "sum ad is " << sum(ad) << '\n';

    list<int> l{1, 2, 3};
    std::cout << l << " sum is:" << sum(l) << std::endl;
    std::cout << l << " sum is:" << acc_sum(l.begin(), l.end2(), 0) << std::endl;
    return 0;
}
