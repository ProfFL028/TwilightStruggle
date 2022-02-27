#include <iostream>
#include <bitset>
#include "crc.h"

using namespace std;

unsigned int CRC::generator = 0xedb88320; // reversed, 0x04C11DB7: msb first
unsigned int CRC::crcTable[256];

void CRC::resetGenerator(unsigned int newGenerator) {
    CRC::generator = newGenerator;
    CRC::initCRCTable();
}

void CRC::initCRCTable() {
    for (int i = 0; i < 256; i++) {
        auto crc = (unsigned int) i;
        for (int k = 0; k < 8; k++) {
            if (crc & k) { // short for (crc & k) != 0
                crc = CRC::generator ^ (crc >> 1);
            } else {
                crc >> 1;
            }
        }
        CRC::crcTable[i] = crc;
    }
}

unsigned int CRC::crc32(char *buffer, int len, unsigned int crc) {
    for (int i = 0; i < len; i++) {
        crc = CRC::crcTable[(crc ^ buffer[i]) & 0xff] ^ (crc >> 8);
    }
    return crc;
}


void CRC::testSimpleCRC8() {
    unsigned int generator = 0x1D;
    unsigned int crc = 0;
    unsigned int curByte = 0x02;
    cout << "generator: " << bitset<8>(generator) << endl;
    crc ^= curByte;
    for (int i = 0; i < 8; i++) {
        if ((crc & 0x80) != 0) {
            crc = (crc << 1) ^ generator;
        } else {
            crc <<= 1;
        }
        cout << "step " << i << " : " << bitset<8>(crc) << endl;
    }
    cout << "crc: " << bitset<8>(crc) << endl;
}