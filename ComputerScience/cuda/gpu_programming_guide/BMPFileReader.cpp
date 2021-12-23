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

BMPFile* BMPFileReader::read(const char *fileName) {
    inputStream.open(fileName, ios::in | ios::binary);

    if (inputStream.is_open()) {

        // read bitmap header.
        BMPFileHeader* header = new BMPFileHeader();
        inputStream.read((char *) &header->fileType, sizeof(unsigned char) * 2);
        inputStream.read((char *) &header->fileSize, sizeof(header->fileSize));
        inputStream.read((char *) &header->reserved1, sizeof(header->reserved1));
        inputStream.read((char *) &header->reserved2, sizeof(header->reserved2));
        inputStream.read((char *) &header->offsetData, sizeof(header->offsetData));

        // read bitmap info.
        BMPFileInfo* info = new BMPFileInfo();
        inputStream.read((char *) &info->headerSize, sizeof(info->headerSize));
        inputStream.read((char *) &info->width, sizeof(info->width));
        inputStream.read((char *) &info->height, sizeof(info->height));
        inputStream.read((char *) &info->planes, sizeof(info->planes));
        inputStream.read((char *) &info->bitCount, sizeof(info->bitCount));
        inputStream.read((char *) &info->compression, sizeof(info->compression));
        inputStream.read((char *) &info->imageSize, sizeof(info->imageSize));
        inputStream.read((char *) &info->xPelsPerMeter, sizeof(info->xPelsPerMeter));
        inputStream.read((char *) &info->yPelsPerMeter, sizeof(info->yPelsPerMeter));
        inputStream.read((char *) &info->clrUsed, sizeof(info->clrUsed));
        inputStream.read((char *) &info->clrImportant, sizeof(info->clrImportant));


        BMPFile* bmpFile = new BMPFile();
        bmpFile->header = header;
        bmpFile->info = info;

        inputStream.close();
        return bmpFile;
    } else {
        return nullptr;
    }
}

