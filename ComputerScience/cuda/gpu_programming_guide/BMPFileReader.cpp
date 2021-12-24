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

BMPFile *BMPFileReader::read(const char *fileName) {
    inputStream.open(fileName, ios::in | ios::binary);

    if (inputStream.is_open()) {
        // read bitmap header.
        BMPFileHeader *header = new BMPFileHeader();
        inputStream.read((char *) &header->fileType, sizeof(unsigned char) * 2);
        inputStream.read((char *) &header->fileSize, sizeof(header->fileSize));
        inputStream.read((char *) &header->reserved1, sizeof(header->reserved1));
        inputStream.read((char *) &header->reserved2, sizeof(header->reserved2));
        inputStream.read((char *) &header->offsetData, sizeof(header->offsetData));

        // read bitmap info.
        BMPFileInfo *info = new BMPFileInfo();
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

        int platteSize = header->offsetData - 14 - info->headerSize;
        unsigned char *platte = new unsigned char[platteSize];
        inputStream.read((char *) platte, sizeof(unsigned char) * platteSize);

        int imgSize = info->imageSize;
        unsigned char *imgData = new unsigned char[imgSize];
        inputStream.read((char *) imgData, sizeof(unsigned char) * imgSize);

        BMPFile *bmpFile = new BMPFile();
        bmpFile->header = header;
        bmpFile->info = info;
        bmpFile->platte = platte;
        bmpFile->imgData = imgData;
        bmpFile->rowBytes = (info->width + 3) & (~3);

        inputStream.close();
        return bmpFile;
    } else {
        return nullptr;
    }
}

Color BMPFile::getColorAt(int x, int y) {
    if (x < 0 || x >= info->width || y < 0 || y >= info->height) {
        cerr << "input index error " << endl;
        return Color();
    }
    if (info->height > 0) {
        y = info->height - y - 1;
    }
    int pos = imgData[y * rowBytes + x] << 2;
    Color color;
    color.blue = platte[pos];
    color.green = platte[pos + 1];
    color.red = platte[pos + 2];
    color.alpha = platte[pos + 3];

    return color;
}

void BMPFile::flipH() {
    int centerV = info->width / 2;
    for (int j = 0; j < info->height; j++) {
        int posH = j * rowBytes;
        for (int i = 0; i < centerV; i++) {
            int posOriginal = posH + i;
            int posDest = posH + info->width - 1 - i;
            unsigned char tmp = imgData[posOriginal];
            imgData[posOriginal] = imgData[posDest];
            imgData[posDest] = tmp;
        }
    }
}

void BMPFile::flipV() {
    int centerH = info->height / 2;
    for (int j = 0; j < centerH; j++) {
        int originalH = j * rowBytes;
        int destH = (info->height - 1 - j) * rowBytes;
        for (int i = 0; i < info->width; i++) {
            unsigned char tmp = imgData[originalH + i];
            imgData[originalH + i] = imgData[destH + i];
            imgData[destH + i] = tmp;
        }
    }
}

void BMPFileHeader::save(fstream *outputStream) {
    outputStream->write((char *) &fileType, sizeof(unsigned char) * 2);
    outputStream->write((char *) &fileSize, sizeof(fileSize));
    outputStream->write((char *) &reserved1, sizeof(reserved1));
    outputStream->write((char *) &reserved2, sizeof(reserved2));
    outputStream->write((char *) &offsetData, sizeof(offsetData));
}

void BMPFileInfo::save(fstream *outputStream) {
    outputStream->write((char *) &headerSize, sizeof(headerSize));
    outputStream->write((char *) &width, sizeof(width));
    outputStream->write((char *) &height, sizeof(height));
    outputStream->write((char *) &planes, sizeof(planes));
    outputStream->write((char *) &bitCount, sizeof(bitCount));
    outputStream->write((char *) &compression, sizeof(compression));
    outputStream->write((char *) &imageSize, sizeof(imageSize));
    outputStream->write((char *) &xPelsPerMeter, sizeof(xPelsPerMeter));
    outputStream->write((char *) &yPelsPerMeter, sizeof(yPelsPerMeter));
    outputStream->write((char *) &clrUsed, sizeof(clrUsed));
    outputStream->write((char *) &clrImportant, sizeof(clrImportant));
}

bool BMPFile::save(const char *filename) {
    fstream outputStream(filename, ios::out | ios::trunc | ios::binary);
    if (outputStream.is_open()) {
        header->save(&outputStream);
        info->save(&outputStream);
        int platteSize = header->offsetData - 14 - info->headerSize;
        outputStream.write((char *) platte, sizeof(unsigned char) * platteSize);
        outputStream.write((char *) imgData, sizeof(unsigned char) * info->imageSize);

        //outputStream.write((char*) '\0', sizeof(unsigned char));
        outputStream.close();
        return true;
    } else {
        cerr << "create file: " << filename << " error!" << endl;
        return false;
    }
}


