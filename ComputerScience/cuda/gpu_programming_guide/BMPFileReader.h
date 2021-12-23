//
// Created by proffl on 2021/12/23.
//

#ifndef GPU_PROGRAMMING_GUIDE_BMPFILEREADER_H
#define GPU_PROGRAMMING_GUIDE_BMPFILEREADER_H

#include <iostream>
#include <fstream>

using namespace std;

namespace img {
    struct BMPFileHeader {
        unsigned char fileType[2];
        unsigned fileSize;
        unsigned short reserved1{0};
        unsigned short reserved2{0};
        unsigned offsetData{0};

        friend ostream &operator<<(ostream &ostream, const BMPFileHeader &header) {
            ostream << "bmp file short file type: [ " << header.fileType[0] << header.fileType[1] << " ]" << endl;
            ostream << "bmp file size: [ " << header.fileSize << " ]" << endl;
            ostream << "bmp offset from header to data: [ " << header.offsetData << " ]" << endl;
            return ostream;
        }
    };

    class BMPFileReader {
    public:
        BMPFileReader();

        virtual ~BMPFileReader();

        BMPFileHeader *read(const char *fileName);

    private:
        ifstream inputStream;
    };
}


#endif //GPU_PROGRAMMING_GUIDE_BMPFILEREADER_H
