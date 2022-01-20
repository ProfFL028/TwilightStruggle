#include "LArray.h"
#include <iostream>
#include <cstring>
using namespace std;
using namespace la;

const int LArray::COLUMN_BUF = 256;
const char* LArray::UNAMED = "unamed";

LArray::LArray() {
    this->columnName = nullptr;
    this->datas = nullptr;
    this->length = 0;
}

LArray::LArray(double* datas, int size, const char* columnName) {
    this->columnName = new char[COLUMN_BUF];
    if (columnName != 0 && (strlen(columnName) != 0)) 
        strcpy(this->columnName, columnName);
    else 
        strcpy(this->columnName, UNAMED);
    this->datas = new double[size];
    memcpy(this->datas, datas, size * sizeof(double));
    this->length = size;
}

LArray::LArray(const LArray& v) {
    this->length = v.length;
    this->columnName = new char[COLUMN_BUF];
    if (v.columnName != 0 && (strlen(v.columnName) != 0)) 
        strcpy(this->columnName, v.columnName);
    else 
        strcpy(this->columnName, UNAMED);
    this->datas = new double[v.length];
    memcpy(this->datas, v.datas, v.length * sizeof(double));
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

double& LArray::operator[] (int idx) {
    if (this->length <= idx || idx < 0) {
        char msg[256];
        sprintf(msg, "idx should between 0 and %d", this->length);
        throw invalid_argument(msg);
    }

    return this->datas[idx];
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

LArray& LArray::operator= (const LArray& v) {
    if (this == &v) {
        return *this;
    }
    this->length = v.length;
    if (this->columnName != 0) {
        delete [] this->columnName;
    }
    this->columnName = new char[COLUMN_BUF];
    if (v.columnName != 0 && (strlen(v.columnName) != 0)) 
        strcpy(this->columnName, v.columnName);
    else 
        this->columnName = (char*) "unnamed";

    if (this->datas != 0) {
        delete [] this->datas;
    }
    this->datas = new double[v.length];
    memcpy(this->datas, v.datas, v.length * sizeof(double));

    return *this;
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