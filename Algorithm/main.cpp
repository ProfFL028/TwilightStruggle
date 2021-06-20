#include <iostream>

#include "BigInteger.h"


int main() {
    char *a = "16549843132165467985641313216549879451613123131123134567891316549";
    char *b = "165498431321654679856413132165498794516131231313564983169";

    int lengthA = strlen(a);
    int lengthB = strlen(b);

    for (int i = 0; i < lengthA; i++) {

    }


    char result[200];
    memset(result, 0, sizeof(result));
    int extra = 0;
    for (int i = 0; i < strlen(a); i++) {
        result[i] = a[i];
    }
    for (int j = 0; j < strlen(b); j++) {
        int t = j < strlen(a)? result[j] - '0' : 0;
        int intValue = t + b[j] - '0' + extra;
        extra = intValue / 10;
        result[j] = intValue % 10 + '0';
    }
    if (extra > 0) {
        std::cout <<"I'm here" << std::endl;
        result[strlen(a)] = extra + '0';
    }
    std::cout << result << std::endl;
    return 0;
}
