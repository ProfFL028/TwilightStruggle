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
        unsigned char fileType[3]{0};
        unsigned fileSize{0};
        unsigned short reserved1{0};
        unsigned short reserved2{0};
        unsigned offsetData{0};

        friend ostream &operator<<(ostream &ostream, const BMPFileHeader &header) {
            ostream << "bmp file short file type:       [ " << header.fileType << " ]" << endl;
            ostream << "bmp file size:                  [ " << header.fileSize << " ]" << endl;
            ostream << "bmp offset from header to data: [ " << header.offsetData << " ]" << endl;
            return ostream;
        }
        void save(fstream* outputStream);
    };

    struct BMPFileInfo {
        unsigned headerSize{0};
        int width{0};
        int height{0};
        unsigned short planes{0}; // image color planes
        unsigned short bitCount{0}; // bit/pixel
        unsigned compression{0}; // 0-5
        unsigned imageSize{0};
        unsigned xPelsPerMeter{0};
        unsigned yPelsPerMeter{0};
        unsigned clrUsed{0};
        unsigned clrImportant{0};

        friend ostream &operator<<(ostream &ostream, const BMPFileInfo &info) {
            ostream << "bmp header size:                [ " << info.headerSize << " ]" << endl;
            ostream << "bmp width:                      [ " << info.width << " ]" << endl;
            ostream << "bmp height:                     [ " << info.height << " ]" << endl;
            ostream << "bmp color planes:               [ " << info.planes << " ]" << endl;
            ostream << "bmp bit count:                  [ " << info.bitCount << " ]" << endl;
            ostream << "bmp compression:                [ " << info.compression << " ]" << endl;
            ostream << "bmp image size:                 [ " << info.imageSize << " ]" << endl;
            ostream << "bmp xPelsPerMeter:              [ " << info.xPelsPerMeter << " ]" << endl;
            ostream << "bmp yPelsPerMeter:              [ " << info.yPelsPerMeter << " ]" << endl;
            ostream << "bmp clrUsed:                    [ " << info.clrUsed << " ]" << endl;
            ostream << "bmp clrImportant:               [ " << info.clrImportant << " ]" << endl;
            return ostream;
        }

        void save(fstream* outputStream);
    };

    struct Color {
        unsigned char blue{0};
        unsigned char green{0};
        unsigned char red{0};
        unsigned char alpha{0};

        friend ostream &operator<<(ostream &ostream, const Color &color) {
            ostream << "rgba(" << int(color.red) << ", "
                    << int(color.green) << ", "
                    << int(color.blue) << ", "
                    << int(color.alpha) << ")" << endl;
            return ostream;
        }
    };

    class BMPFile {
    public:
        BMPFileHeader *header;
        BMPFileInfo *info;
        unsigned char *platte;
        unsigned char *imgData;
        int rowBytes = 0;

        void flipH();
        void flipV();

        int numThreads = 2;

        bool save(const char* filename);

        friend ostream &operator<<(ostream &ostream, const BMPFile &file) {
            ostream << *file.header << *file.info << endl;
            return ostream;
        }

        Color getColorAt(int x, int y);
    };

    class BMPFileReader {
    public:
        BMPFileReader();

        virtual ~BMPFileReader();

        BMPFile *read(const char *fileName);

    private:
        ifstream inputStream;
    };
};



#endif //GPU_PROGRAMMING_GUIDE_BMPFILEREADER_H
