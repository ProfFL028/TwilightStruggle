#include <iostream>
#include <initializer_list>

using namespace std;

template<class T>
class my_vector {
public:
    my_vector(size_t new_size) : data_size{new_size}, data{new T[new_size]} {}

//    my_vector(const my_vector &v) : data_size{v.data_size}, data{new T[v.data_size]} {
//        for (int i = 0; i < data_size; ++i) {
//            data[i] = v.data[i];
//        }
//    }

    my_vector(my_vector &&v) noexcept : data_size{v.data_size}, data{new T[v.data_size]}  {
        v.data = nullptr;
        v.data_size = 0;
    }

    my_vector(initializer_list<T> values) : data_size(values.size()), data{new T[values.size()]} {
        copy(begin(values), end(values), data);
    }

    my_vector &operator=(initializer_list<T> values) {
        assert(data_size == values.size());
        copy(begin(values), end(values), data);
        return *this;
    }

    my_vector& operator=(my_vector<T>&& src) {
        assert(data_size == src.data_size);
        delete [] data;
        swap(data, src.data);
        swap(data_size, src.data_size);
        src.data = nullptr;
        src.data_size = 0;
        return *this;
    }

    ~my_vector() { delete[] data; }


    inline my_vector<int> ones(int n) {
        my_vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            v.data[i] = 1;
        }
        return v;
    }

public:
    friend ostream &operator<<(ostream &out, const my_vector &v) {
        out << "[";
        for (int i = 0; i < v.data_size; ++i) {
            out << v.data[i] << ", ";
        }
        out << "\b\b]";
        return out;
    }

private:
    size_t data_size;
    T *data;
};

class complex {
public:
    float r, l;

    friend ostream &operator<<(ostream &out, const complex &c) {
        out << "(";
        out << c.r << ", " << c.l << ")";
        return out;
    }
};

int main() {
    my_vector<double> v1{1.0, 2.0, 3.0};
    cout << v1 << endl;

    my_vector<complex> vc = {{2.0, 3.0}};
    cout << vc << endl;
    return 0;
}