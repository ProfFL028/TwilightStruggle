#include <iostream>
#include "BMPFileReader.h"

using namespace std;
using namespace img;

int main() {
    BMPFileReader reader;
    BMPFile *file = reader.read("tree.bmp");

    cout << *file << endl;

    cout << file->getColorAt(63, 50) <<endl;
    cout << file->getColorAt(0, 0) <<endl;
    cout << file->getColorAt(374, 0) <<endl;
    cout << file->getColorAt(0, 499) <<endl;
    cout << file->getColorAt(374, 499) <<endl;


    return 0;
}
