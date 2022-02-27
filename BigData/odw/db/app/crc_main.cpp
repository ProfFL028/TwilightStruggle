#include <iostream>
#include <bitset>
#include "crc.h"

using namespace std;


int main() {
    CRC::initCRCTable();
    char text[] = "abc";
    unsigned int result = CRC::crc32(text, 3, 0xFFFFFFFF);
    cout << hex << result << ": " << bitset<32>(result) << endl;
    return 0;
}
