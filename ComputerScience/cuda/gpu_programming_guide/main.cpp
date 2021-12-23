#include <iostream>
#include <fstream>
#include <bitset>
#include "BMPFileReader.h"

using namespace std;
using namespace img;

int main() {
    BMPFileReader reader;
    BMPFileHeader *header = reader.read("tree.bmp");

    cout << *header;

    return 0;
}
