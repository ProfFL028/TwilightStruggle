#include <iostream>
#include <tuple>

std::tuple<int, int, int> get_rgb_elements_as_a_tuple(int r, int g, int b) {
    return std::make_tuple(r, g, b);
}

int main() {
    int r1=212; int g1=24; int b1=118;
    int r2=0; int g2=0; int b2=0;
    int r3=0; int g3=0; int b3=0;
    std::tuple<int, int, int> rgb;

    std::cout << "r1: " << r1 << " g1: " << g1 << " b1: " << b1 << std::endl;
    std::cout << "r2: " << r2 << " g2: " << g2 << " b2: " << b2 << std::endl;
    std::cout << "r3: " << r3 << " g3: " << g3 << " b3: " << b3 << std::endl;

    std::cout << "rgb=get_rgb_elements_as_a_tuple(r1, g1, b1);" << std::endl;
    rgb=get_rgb_elements_as_a_tuple(r1, g1, b1);

    // unroll #1
    std::cout << "unroll #1" << std::endl;
    r2=std::get<0>(rgb);
    g2=std::get<1>(rgb);
    b2=std::get<2>(rgb);
    std::cout << "r2=std::get<0>(rgb); g2=std::get<1>(rgb); b2=std::get<2>(rgb);" << std::endl;
    std::cout << "r1: " << r1 << " g1: " << g1 << " b1: " << b1 << std::endl;
    std::cout << "r2: " << r2 << " g2: " << g2 << " b2: " << b2 << std::endl;
    std::cout << "r3: " << r3 << " g3: " << g3 << " b3: " << b3 << std::endl;
    // unroll #2
    std::cout << "unroll #2" << std::endl;
    std::tie(r3, g3, b3) = rgb;
    std::cout << "std::tie(r3, g3, b3) = rgb;" << std::endl;
    std::cout << "r1: " << r1 << " g1: " << g1 << " b1: " << b1 << std::endl;
    std::cout << "r2: " << r2 << " g2: " << g2 << " b2: " << b2 << std::endl;
    std::cout << "r3: " << r3 << " g3: " << g3 << " b3: " << b3 << std::endl;

    return 0;
}
