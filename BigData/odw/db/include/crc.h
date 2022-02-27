
#ifndef DATABASE_CRC_H
#define DATABASE_CRC_H

/**
 * understanding CRC: http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html
 *
 * usage: call CRC::initCRCTable() first!!!
 * CRC::crc32("123456789", 12, 0xFFFFFFFF)
 */
class CRC {
private:
    CRC() { }
    virtual ~CRC() { }

public:
    static void resetGenerator(unsigned int newGenerator);
    static void initCRCTable();

    static unsigned int crc32(char* buffer, int len, unsigned int crc);
private:
    static unsigned int generator;
    static unsigned int crcTable[256];

public:
    // for learning purpose only.
    static void testSimpleCRC8();
};

#endif //DATABASE_CRC_H
