// Compile: clang++ -std=c++17 02_index.cpp -o 02_index

#include <iostream>

int get_index(int x, int y, int width)
{
    return x+width*y;
}

int main()
{
    int width=10;
    int x=0;
    int y=0;

    std::cout << "Index: " << get_index(x,y,width) << " (for X:" << x << " Y:" << y << ")" << std::endl;
    y=1;x=5;
    std::cout << "Index: " << get_index(x,y,width) << " (for X:" << x << " Y:" << y << ")" << std::endl;
    y=2;x=3;
    std::cout << "Index: " << get_index(x,y,width) << " (for X:" << x << " Y:" << y << ")" << std::endl;
    y=3;x=2;
    std::cout << "Index: " << get_index(x,y,width) << " (for X:" << x << " Y:" << y << ")" << std::endl;
    y=4;x=3;
    std::cout << "Index: " << get_index(x,y,width) << " (for X:" << x << " Y:" << y << ")" << std::endl;
    y=6;x=6;
    std::cout << "Index: " << get_index(x,y,width) << " (for X:" << x << " Y:" << y << ")" << std::endl;
    y=7;x=2;
    std::cout << "Index: " << get_index(x,y,width) << " (for X:" << x << " Y:" << y << ")" << std::endl;
    y=9;x=8;
    std::cout << "Index: " << get_index(x,y,width) << " (for X:" << x << " Y:" << y << ")" << std::endl << std::endl;

    std::cout << " 0123456789" << std::endl;
    std::cout << "0+---------- I: 0" << std::endl;
    std::cout << "1-----+----- I: 15" << std::endl;
    std::cout << "2---+------- I: 23" << std::endl;
    std::cout << "3--+-------- I: 32" << std::endl;
    std::cout << "4---+------- I: 43" << std::endl;
    std::cout << "5----------- N/A" << std::endl;
    std::cout << "6------+---- I: 66" << std::endl;
    std::cout << "7--+-------- I: 72" << std::endl;
    std::cout << "8----------- N/A" << std::endl;
    std::cout << "9--------+-- I: 98" << std::endl;

    return 0;
}