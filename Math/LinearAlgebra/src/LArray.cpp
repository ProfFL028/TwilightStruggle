#include "LArray.h"
#include <iostream>
using namespace std;
using namespace la;

int LArray::COLUMN_BUF = 256;

LArray::LArray() {
}

LArray::LArray(double* datas, int size, const char* columnName) {
    this->columnName = new char[COLUMN_BUF];
    if (columnName != 0 && (strlen(columnName) != 0)) 
        strcpy(this->columnName, columnName);
    else 
        this->columnName = (char*) "unnamed";
    this->datas = new double[size];
    memcpy(this->datas, datas, size);
    this->length = size;
}

LArray* LArray::ones(int size, const char* columnName) {
    return LArray::constant(1, size, columnName);
}

LArray* LArray::zeros(int size, const char* columnName) {
    return LArray::constant(0, size, columnName);
}

LArray* LArray::constant(int v, int size, const char* columnName) {
    double* datas = new double[size];
    for (int i = 0; i < size; i++) {
        datas[i] = v;
    }
    LArray* arr = new LArray(datas, size, columnName);
    delete [] datas;
    return arr;
}


LArray* LArray::add(double v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] += v;
    }
    return this;
}

LArray* LArray::minus(double v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] -= v;
    }
    return this;
}

LArray* LArray::multi(double v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] *= v;
    }
    return this;
}

LArray* LArray::div(double v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] /= v;
    }
    return this;
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