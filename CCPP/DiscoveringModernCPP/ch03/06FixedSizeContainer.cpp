#include <iostream>

template<class T, std::size_t Size>
class fixed_size_container {
public:
    using self = fixed_size_container;
    static constexpr std::size_t my_size = Size;

    fixed_size_container(std::size_t s = Size) { assert(s == Size); }

    self &copy(const self &that) {
        std::copy(that.data, that.data + Size, data);
        return *this;
    }

    T &operator[](std::size_t i) const {
        return data[i];
    }

    self operator+(const self &that) {
        self result;
        for (auto i = 0; i < Size; i++) {
            result[i] = data[i] + that[i];
        }
        return result;
    }

private:
    T data[my_size];
};

template<typename T, T value>
struct t_const;
using false_type = t_const<bool, false>;


template<auto Value>
struct integral_constant_c: std::integral_constant<decltype(Value), Value>{};
using f_type = integral_constant_c<false>;

template<auto Value>
using integral_constant_t = std::integral_constant<decltype(Value), Value>;
using t_type = integral_constant_t<true>;

int main() {
    return 0;
}