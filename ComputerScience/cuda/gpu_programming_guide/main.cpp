#include <iostream>
#include "BMPFileReader.h"

using namespace std;
using namespace img;

int main() {
    BMPFileReader reader;
    BMPFile *file = reader.read("tree.bmp");

    cout << *file << endl;

    cout << file->getColorAt(63, 50) <<endl;

    file->flipH();
    file->save("treeV.bmp");

    file->flipV();
    file->save("treeVH.bmp");


    return 0;
}
