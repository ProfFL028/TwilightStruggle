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
    this->dataOwner = false;
}

LArray::LArray(const LArray& v) {
    this->setDatas(v.datas, v.length);
    this->setColumnName(v.columnName);
    this->dataOwner = false;
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

LArray LArray::operator+ (const double& v) const {
    LArray result;
    result.columnName = new char[COLUMN_BUF];
    strcpy(result.columnName, this->columnName);
    result.datas = new double[this->length];
    result.length = this->length;

    for (int i = 0; i < this->length; i++) {
        result.datas[i] = this->datas[i] + v;
    }
    return result;
}

LArray LArray::operator- (const double& v) const {
    LArray result;
    result.columnName = new char[COLUMN_BUF];
    strcpy(result.columnName, this->columnName);
    result.datas = new double[this->length];
    result.length = this->length;

    for (int i = 0; i < this->length; i++) {
        result.datas[i] = this->datas[i] - v;
    }
    return result;
}

LArray LArray::operator* (const double& v) const {
    LArray result;
    result.columnName = new char[COLUMN_BUF];
    strcpy(result.columnName, this->columnName);
    result.datas = new double[this->length];
    result.length = this->length;

    for (int i = 0; i < this->length; i++) {
        result.datas[i] = this->datas[i] * v;
    }
    return result;
}

LArray LArray::operator/ (const double& v) const {
    LArray result;
    result.columnName = new char[COLUMN_BUF];
    strcpy(result.columnName, this->columnName);
    result.datas = new double[this->length];
    result.length = this->length;

    for (int i = 0; i < this->length; i++) {
        result.datas[i] = this->datas[i] / v;
    }
    return result;
}

LArray& LArray::operator+= (const double& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] += v;
    }
    return *this;
}

LArray& LArray::operator-= (const double& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] -= v;
    }
    return *this;
}

LArray& LArray::operator*= (const double& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] *= v;
    }
    return *this;
}

LArray& LArray::operator/= (const double& v) {
    for (int i = 0; i < this->length; i++) {
        this->datas[i] /= v;
    }
    return *this;
}


LArray LArray::operator+ (const LArray& l1) const {
    if (this->length == 0 || l1.length == 0) {
        throw invalid_argument("array should be initialized!");
    }
    int arrLength = max(this->length, l1.length);
    LArray* result = new LArray();
    result->datas = new double[arrLength];
    result->length = arrLength;
    result->columnName = new char[COLUMN_BUF];
    strcpy(result->columnName, this->columnName);

    for (int i = 0; i < arrLength; i++) {
        result->datas[i] = this->datas[(i % this->length)] + l1.datas[(i % l1.length)];
    }
    return *result;
}

LArray LArray::operator- (const LArray& l1) const {
    if (this->length == 0 || l1.length == 0) {
        throw invalid_argument("array should be initialized!");
    }
    int arrLength = max(this->length, l1.length);
    LArray* result = new LArray();
    result->datas = new double[arrLength];
    result->length = arrLength;
    result->columnName = new char[COLUMN_BUF];
    strcpy(result->columnName, this->columnName);

    for (int i = 0; i < arrLength; i++) {
        result->datas[i] = this->datas[(i % this->length)] - l1.datas[(i % l1.length)];
    }
    return *result;
}

LArray LArray::operator* (const LArray& l1) const {
    if (this->length == 0 || l1.length == 0) {
        throw invalid_argument("array should be initialized!");
    }
    int arrLength = max(this->length, l1.length);
    LArray* result = new LArray();
    result->datas = new double[arrLength];
    result->length = arrLength;
    result->columnName = new char[COLUMN_BUF];
    strcpy(result->columnName, this->columnName);

    for (int i = 0; i < arrLength; i++) {
        result->datas[i] = this->datas[(i % this->length)] * l1.datas[(i % l1.length)];
    }
    return *result;
}

LArray LArray::operator/ (const LArray& l1) const {
    if (this->length == 0 || l1.length == 0) {
        throw invalid_argument("array should be initialized!");
    }
    int arrLength = max(this->length, l1.length);
    LArray* result = new LArray();
    result->datas = new double[arrLength];
    result->length = arrLength;
    result->columnName = new char[COLUMN_BUF];
    strcpy(result->columnName, this->columnName);

    for (int i = 0; i < arrLength; i++) {
        result->datas[i] = this->datas[(i % this->length)] / l1.datas[(i % l1.length)];
    }
    return *result;
}

LArray& LArray::add(const LArray& v) {
    if (this->length < v.length) {
        double* tmp = new double[v.length];
        memcpy(tmp, this->datas, v.length * sizeof(double));
        delete [] this->datas;
        this->datas = tmp;
        this->length = v.length;
    }
    for (int i = 0; i < this->length; i++) {
        this->datas[i] = this->datas[i] + v.datas[(i % v.length)];
    }

    return *this;
}

LArray& LArray::minus(const LArray& v) {
    if (this->length < v.length) {
        double* tmp = new double[v.length];
        memcpy(tmp, this->datas, v.length * sizeof(double));
        delete [] this->datas;
        this->datas = tmp;
        this->length = v.length;
    }
    for (int i = 0; i < this->length; i++) {
        this->datas[i] = this->datas[i] - v.datas[(i % v.length)];
    }

    return *this;
}

LArray& LArray::multi(const LArray& v) {
    if (this->length < v.length) {
        double* tmp = new double[v.length];
        memcpy(tmp, this->datas, v.length * sizeof(double));
        delete [] this->datas;
        this->datas = tmp;
        this->length = v.length;
    }
    for (int i = 0; i < this->length; i++) {
        this->datas[i] = this->datas[i] * v.datas[(i % v.length)];
    }

    return *this;
}

LArray& LArray::div(const LArray& v) {
    if (this->length < v.length) {
        double* tmp = new double[v.length];
        memcpy(tmp, this->datas, v.length * sizeof(double));
        delete [] this->datas;
        this->datas = tmp;
        this->length = v.length;
    }
    for (int i = 0; i < this->length; i++) {
        this->datas[i] = this->datas[i] / v.datas[(i % v.length)];
    }

    return *this;
}

LArray& LArray::operator+=(const LArray& v) {
    return this->add(v);
}

LArray& LArray::operator-=(const LArray& v) {
    return this->minus(v);
}

LArray& LArray::operator*=(const LArray& v) {
    return this->multi(v);
}

LArray& LArray::operator/=(const LArray& v) {
    return this->div(v);
}

