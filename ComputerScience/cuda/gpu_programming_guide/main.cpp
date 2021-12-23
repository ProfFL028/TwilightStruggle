#include <iostream>
#include "BMPFileReader.h"

using namespace std;
using namespace img;

int main() {
    BMPFileReader reader;
    BMPFile *file = reader.read("tree.bmp");

    cout << *file << endl;


    return 0;
}
