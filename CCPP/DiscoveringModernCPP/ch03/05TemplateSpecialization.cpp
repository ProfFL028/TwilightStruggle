#include <iostream>
#include <complex>

template<class T>
class vector {

};

class vector_bool_proxy {
public:
    vector_bool_proxy(unsigned char &b, std::size_t p) : byte{b}, mask{static_cast<unsigned char>(1 << p)} {}

    operator bool() const {
        return byte & mask;
    }

    vector_bool_proxy &operator=(bool b) {
        if (b) {
            byte |= mask;
        } else {
            byte &= ~mask;
        }
        return *this;
    }

private:
    unsigned char &byte;
    unsigned char mask;
};

template<>
class vector<bool> {
public:
    explicit vector(std::size_t size) : size{size}, data{new unsigned char[(size + 7) / 8]} {
    }

    // simple but hard to use.
//    bool operator[](std::size_t i) const {
//        return (data[i / 8] >> i % 8) & 1;
//    }

    vector_bool_proxy operator[](std::size_t i) const {
        return {data[i / 8], i % 8};
    }

    vector() : size{0} {}

private:
    std::size_t size;
    std::unique_ptr<unsigned char[]> data;
};


// avoid specialization templates in functions.
template<typename T>
struct abs_factor {
    typedef T result_type;
    T operator()(const T& x) {
        return x < T(0) ? -x: x;
    }
};

template<typename T>
struct abs_factor<std::complex<T>> {
    typedef T result_type;
    T operator()(const std::complex<T>& x) {
        return sqrt(x.imag()*x.imag() + x.real() * x.real());
    }
};

template<typename T>
decltype(auto) abs(const T &x) {
    return abs_factor<T>{}(x);
}


// auto abs(const T& x) -> decltype(abs_factor<T>{}(x))

int main() {
    vector<bool> bs(12);

    bs[0] = true;
    bs[4] = true;
    bs[9] = true;
    for (int i = 0; i < 12; i++) {
        std::cout << i << "->" << bs[i].operator bool() << std::endl;
    }
    return 0;
}