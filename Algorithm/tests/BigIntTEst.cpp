#include <iostream>
#include "../dataStructure/Vector.cpp"

int main() {
    char *a = "9999999932165467985641313216549879451613123131123134567891316549";
    char *b = "165498431321654679856413132165498794516131231313564983169";

    int lengthA = strlen(a);
    int lengthB = strlen(b);

    Vector<char> result;

    int extra = 0;
    for (int i = 0; i < lengthB; i++) {
        int value = a[lengthA - i - 1] - '0' + b[lengthB - i - 1] - '0' + extra;
        result.add((value % 10) + '0');
        extra = value / 10;
    }
    int lengthDiff = lengthA - lengthB;
    for (int i = 0; i < lengthDiff; i++) {
        int value = a[lengthDiff - i - 1] - '0' + extra;
        result.add((value % 10) + '0');
        extra = value / 10;
    }
    if (extra > 0)
        result.add(extra + '0');

    std::cout << ' ' << a << std::endl;
    std::cout << '+';
    for (int i =0; i < lengthA - lengthB; i++) {
        std::cout<< ' ';
    }
    std::cout<< b << std::endl;
    if (extra == 0) {
        std::cout<< ' ';
    }
    result.print();

    return 0;
}
