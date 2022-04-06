
#include "StringUtils.h"
#include <iostream>

using namespace std;
using namespace utils;

int main() {
    char * uri = "https://www.me.com/%215";
    char* uriDecoded = uriDecode(uri, 23);
    cout << uriDecoded << endl;
    return 0;
};