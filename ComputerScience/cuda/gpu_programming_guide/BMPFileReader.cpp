//
// Created by proffl on 2021/12/23.
//

#include "BMPFileReader.h"

using namespace std;
using namespace img;

BMPFileReader::BMPFileReader() {
}

BMPFileReader::~BMPFileReader() {
    if (inputStream.is_open()) {
        inputStream.close();
    }
}

BMPFileHeader* BMPFileReader::read(const char *fileName) {
    inputStream.open(fileName, ios::in | ios::binary);
    if (inputStream.is_open()) {
        BMPFileHeader* header = new BMPFileHeader();

        inputStream.read((char*)header, sizeof(BMPFileHeader));

        return header;
    } else {
        return nullptr;
    }
}

