#include "LArray.h"
#include <iostream>
#include <cstring>
using namespace std;
using namespace la;

const int LArray::COLUMN_BUF = 256;
const char* LArray::UNAMED = "unamed";

LArray::LArray() {
}

LArray::LArray(double* datas, const int& size, const char* columnName) {
    this->setDatas(datas, size);
    this->setColumnName(columnName);
    this->dataOwner = true;
}

LArray::LArray(const LArray& v) {
    this->copyDatas(v.datas, v.length);
    this->setColumnName(v.columnName);
}

void LArray::copy(const LArray& v) {
    this->copyDatas(v.datas, v.length);
    this->setColumnName(v.columnName);
}

void LArray::setDatas(double* datas, const int& length) {
    this->cleanData();
    this->datas = datas;
    this->length = length;
    this->dataOwner = false;
}

void LArray::setColumnName(const char* columnName) {
    this->cleanColumnName();
    
    this->columnName = new char[COLUMN_BUF];
    if (columnName != nullptr && strlen(columnName) != 0) {
        strcpy(this->columnName, columnName);
    } else {
        strcpy(this->columnName, UNAMED);
    }
}

void LArray::copyDatas(const double* datas, const int& length) {
    this->cleanData();
    this->datas = new double[length];
    memcpy(this->datas, datas, sizeof(double) * length);
    this->length = length;

    this->dataOwner = true;
}

void LArray::clean() {
    this->cleanColumnName();
    if (dataOwner) {
        this->cleanData();
    }
}

void LArray::cleanData() {
    if (this->datas != nullptr) {
        delete [] this->datas;
    }
    this->length = 0;
    this->datas = nullptr;
}

void LArray::cleanColumnName() {
    if (this->columnName != nullptr) {
        delete [] this->columnName;
    }
    this->columnName = nullptr;
}

LArray::~LArray() {
    this->clean();
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

LArray* LArray::ones(const int& size, const char* columnName) {
    return LArray::constant(1, size, columnName);
}

LArray* LArray::zeros(const int& size, const char* columnName) {
    return LArray::constant(0, size, columnName);
}

LArray* LArray::constant(const int& v, const int& size, const char* columnName) {
    double* datas = new double[size];
    for (int i = 0; i < size; i++) {
        datas[i] = v;
    }
    LArray* arr = new LArray(datas, size, columnName);
    return arr;
}

LArray& LArray::operator= (const LArray& v) {
    if (this == &v) {
        return *this;
    }
    this->clean();
    this->copyDatas(v.datas, v.length); // notice using copy instead of set!!!.
    this->setColumnName(v.columnName);

    return *this;
}

double& LArray::operator[] (int idx) {
    if (this->length <= idx || idx < 0) {
        char msg[256];
        sprintf(msg, "idx should between 0 and %d", this->length);
        throw invalid_argument(msg);
    }

    return this->datas[idx];
}

LArray* LArray::add(const double& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] += v;
    }
    return this;
}

LArray* LArray::minus(const double& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] -= v;
    }
    return this;
}

LArray* LArray::multi(const double& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] *= v;
    }
    return this;
}

LArray* LArray::div(const double& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] /= v;
    }
    return this;
}

LArray LArray::operator+ (const double& v) const {
    LArray result(*this);
    result.add(v);
    return result;
}

LArray LArray::operator- (const double& v) const {
    LArray result(*this);
    result.minus(v);
    return result;
}

LArray LArray::operator* (const double& v) const {
    LArray result(*this);
    result.multi(v);
    return result;
}

LArray LArray::operator/ (const double& v) const {
    LArray result(*this);
    result.div(v);
    return result;
}

LArray& LArray::operator+= (const double& v) {
    this->add(v);
    return *this;
}

LArray& LArray::operator-= (const double& v) {
    this->minus(v);
    return *this;
}

LArray& LArray::operator*= (const double& v) {
    this->multi(v);
    return *this;
}

LArray& LArray::operator/= (const double& v) {
    this->div(v);
    return *this;
}

LArray LArray::operator+ (const LArray& l1) const {
    if (this->length == 0) {
        return LArray(l1);
    }
    if (l1.length == 0) {
        return LArray(*this);
    }

    LArray result;
    int arrLength = max(this->length, l1.length);
    result.datas = new double[arrLength];
    for (int i = 0; i < arrLength; i++) {
        result.datas[i] = this->datas[(i % this->length)] + l1.datas[(i % l1.length)];
    }
    result.length = arrLength;
    return result;
}

LArray LArray::operator- (const LArray& l1) const {
    if (this->length == 0) {
        return LArray(l1);
    }
    if (l1.length == 0) {
        return LArray(*this);
    }

    LArray result;
    int arrLength = max(this->length, l1.length);
    result.datas = new double[arrLength];
    for (int i = 0; i < arrLength; i++) {
        result.datas[i] = this->datas[(i % this->length)] - l1.datas[(i % l1.length)];
    }
    result.length = arrLength;
    return result;
}

LArray LArray::operator* (const LArray& l1) const {
    if (this->length == 0) {
        return LArray(l1);
    }
    if (l1.length == 0) {
        return LArray(*this);
    }

    LArray result;
    int arrLength = max(this->length, l1.length);
    result.datas = new double[arrLength];
    for (int i = 0; i < arrLength; i++) {
        result.datas[i] = this->datas[(i % this->length)] * l1.datas[(i % l1.length)];
    }
    result.length = arrLength;
    return result;
}

LArray LArray::operator/ (const LArray& l1) const {
    if (this->length == 0) {
        return LArray(l1);
    }
    if (l1.length == 0) {
        return LArray(*this);
    }

    LArray result;
    int arrLength = max(this->length, l1.length);
    result.datas = new double[arrLength];
    for (int i = 0; i < arrLength; i++) {
        result.datas[i] = this->datas[(i % this->length)] / l1.datas[(i % l1.length)];
    }
    result.length = arrLength;
    return result;
}

LArray* LArray::add(const LArray& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] = this->datas[i] + v.datas[(i % v.length)];
    }

    return this;
}

LArray* LArray::minus(const LArray& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] = this->datas[i] - v.datas[(i % v.length)];
    }

    return this;
}

LArray* LArray::multi(const LArray& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] = this->datas[i] * v.datas[(i % v.length)];
    }

    return this;
}

LArray* LArray::div(const LArray& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] = this->datas[i] / v.datas[(i % v.length)];
    }

    return this;
}

LArray& LArray::operator+=(const LArray& v) {
    this->add(v);
    return *this;
}

LArray& LArray::operator-=(const LArray& v) {
    this->minus(v);
    return *this;
}

LArray& LArray::operator*=(const LArray& v) {
    this->multi(v);
    return *this;
}

LArray& LArray::operator/=(const LArray& v) {
    this->div(v);
    return *this;
}

