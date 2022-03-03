#ifndef DATABASE_TYPEUTIL_HPP
#define DATABASE_TYPEUTIL_HPP

#include <iostream>

namespace util {
    struct common {
    };

    template<typename T>
    struct is_uniform_int {
        static constexpr bool value = std::is_same<T, short>::value
                                      || std::is_same<T, int>::value
                                      || std::is_same<T, long>::value
                                      || std::is_same<T, long long>::value
                                      || std::is_same<T, unsigned short>::value
                                      || std::is_same<T, unsigned int>::value
                                      || std::is_same<T, unsigned long>::value
                                      || std::is_same<T, unsigned long long>::value;
    };

    template<typename T>
    struct is_uniform_real {
        static constexpr bool value = std::is_same<T, float>::value
                                      || std::is_same<T, double>::value
                                      || std::is_same<T, long double>::value;
    };

    template<typename T>
    struct is_uniform_byte {
        static constexpr bool value = std::is_same<T, signed char>::value
                                      || std::is_same<T, unsigned char>::value;
    };

    template<typename T>
    struct is_support_number {
        static constexpr bool value =
                is_uniform_byte<T>::value || is_uniform_int<T>::value || is_uniform_real<T>::value;
    };

    template<typename T>
    struct is_support_character {
        static constexpr bool value = std::is_same<T, char>::value
                                      || std::is_same<T, wchar_t>::value
                                      || std::is_same<T, char16_t>::value
                                      || std::is_same<T, char32_t>::value;
    };

    /**
     * an iterator should have difference_type, pointer, reference, value_type, iterator_category.
     * and check if test(std::declval<T>()) is equal to long
     * @tparam T
     */
    template<typename T>
    struct is_iterator {
    private:
        static char test(...);

        template<typename U,
                typename = typename std::iterator_traits<U>::difference_type,
                typename = typename std::iterator_traits<U>::pointer,
                typename = typename std::iterator_traits<U>::reference,
                typename = typename std::iterator_traits<U>::value_type,
                typename = typename std::iterator_traits<U>::iterator_category>
        static long test(U &&);

    public:
        static constexpr bool value = std::is_same<decltype(test(std::declval<T>())), long>::value;
    };

    template<typename T>
    struct has_reverse {
    private:
        static char test(...);

        template<typename C>
        static long test(decltype(&C::reverse));

    public:
        static constexpr bool value = std::is_same<decltype(test<T>(0)), long>::value;
    };

    template<typename T>
    struct has_inverse {
    private:
        static char test(...);

        template<typename C>
        static long test(decltype(&C::inverse));

    public:
        static constexpr bool value = std::is_same<decltype(test<T>(0)), long>::value;
    };
}

#endif //DATABASE_TYPEUTIL_HPP
