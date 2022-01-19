#include "LArray.h"
#include <iostream>
using namespace std;

int LArray::COLUMN_BUF = 256;

LArray::LArray() {
}

LArray::LArray(double* datas, int size, const char* columnName) {
    this->columnName = new char[COLUMN_BUF];
    strcpy(this->columnName, columnName);
    this->datas = new double[size];
    memcpy(this->datas, datas, size);
    this->length = size;
}

LArray::~LArray() {
    if (this->datas != 0)
        delete [] this->datas;
    if (this->columnName != 0)
        delete [] this->columnName;
    this->length = 0;
}

char* LArray::getColumnName() {
    return this->columnName;
}

double* LArray::getDatas() {
    return this->datas;
}

int LArray::getLength() {
    return this->length;
}