
#include <iostream>
#include "Matrix.h"

using namespace std;
using namespace la;

const short Matrix::MAX_SHAPE_SIZE = 5;

Matrix::Matrix() {
    cout << "info: Matrix empty construct." << endl;
}

Matrix::Matrix(double *data, const short *shape) {
    cout << "info: Matrix data construct." << endl;
    this->setData(data, shape);
}

Matrix::Matrix(const Matrix &m) {
    cout << "info: Matrix copy construct." << endl;
    this->copyData(m.data, m.shape);
}

Matrix::~Matrix() {
    cout << "info: Matrix destruct" << endl;
    this->clean();
}

Matrix *Matrix::constant(const double &v, const short *shape) {
    Matrix *result = new Matrix();
    result->reshape(shape);

    int dataSize = result->getDataSize();
    double *data = new double[dataSize];
    for (int i = 0; i < dataSize; i++) {
        data[i] = v;
    }
    result->setData(data);

    return result;
}

Matrix *Matrix::ones(const short *shape) {
    return Matrix::constant(1, shape);
}

Matrix *Matrix::zeros(const short *shape) {
    return Matrix::constant(0, shape);
}

void Matrix::setData(double *data, const short *shape) {
    this->clean();

    if (shape != nullptr) {
        this->reshape(shape);
    }
    this->data = data;
    this->dataOwner = false;
}

int Matrix::getDataSize() const {
    if (this->shape == nullptr) {
        return 0;
    }
    int dataSize = 1;
    for (int i = 0; i < MAX_SHAPE_SIZE; i++) {
        dataSize *= shape[i];
    }
    return dataSize;
}

void Matrix::copyData(const double *data, const short *shape) {
    this->clean();

    if (shape != nullptr) {
        this->reshape(shape);
    }
    int dataSize = this->getDataSize();
    this->data = new double[dataSize];
    memcpy(this->data, data, dataSize * sizeof(double));
    this->dataOwner = true;
}

void Matrix::reshape(const short *shape) {
    this->shape = new short[MAX_SHAPE_SIZE];
    memcpy(this->shape, shape, MAX_SHAPE_SIZE * sizeof(short));
}

void Matrix::clean() {
    if (this->dataOwner) {
        cout << "info: del data as owner" << endl;
        if (this->data != nullptr) {
            delete[] this->data;
        }
        this->data = nullptr;
    }

    if (this->shape != nullptr) {
        delete[] this->shape;
    }
    this->shape = nullptr;
}

double *Matrix::getData() const {
    return this->data;
}

short *Matrix::getShape() const {
    return this->shape;
}

double &Matrix::operator[](const int &i) {
    return this->data[i];
}

Matrix &Matrix::operator=(const Matrix &v) {
    if (this == &v) {
        return *this;
    }
    this->clean();
    this->copyData(v.data, v.shape);

    return *this;
}

Matrix &Matrix::add(const double &v) {
    for (int i = 0; i <= this->getDataSize(); i++) {
        this->data[i] += v;
    }

    return *this;
}

Matrix &Matrix::minus(const double &v) {
    for (int i = 0; i <= this->getDataSize(); i++) {
        this->data[i] -= v;
    }
    return *this;
}

Matrix &Matrix::multi(const double &v) {
    for (int i = 0; i <= this->getDataSize(); i++) {
        this->data[i] *= v;
    }
    return *this;
}

Matrix &Matrix::div(const double &v) {
    for (int i = 0; i <= this->getDataSize(); i++) {
        this->data[i] /= v;
    }
    return *this;
}

Matrix &Matrix::operator+=(const double &v) {
    return this->add(v);
}

Matrix &Matrix::operator-=(const double &v) {
    return this->minus(v);
}

Matrix &Matrix::operator*=(const double &v) {
    return this->multi(v);
}

Matrix &Matrix::operator/=(const double &v) {
    return this->div(v);
}

Matrix Matrix::operator+(const double &v) {
    Matrix result(*this);
    result.add(v);
    return result;
}

Matrix Matrix::operator-(const double &v) {
    Matrix result(*this);
    result.minus(v);
    return result;
}

Matrix Matrix::operator*(const double &v) {
    Matrix result(*this);
    result.multi(v);
    return result;
}

Matrix Matrix::operator/(const double &v) {
    Matrix result(*this);
    result.div(v);
    return result;
}


Matrix &Matrix::add(const Matrix &v) {
    int myDataSize = this->getDataSize();
    int vDataSize = v.getDataSize();
    if (myDataSize != vDataSize) {
        throw invalid_argument("array shape should be same!!");
    }
    for (int i = 0; i < myDataSize; i++) {
        this->data[i] += v.data[i];
    }
    return *this;
}

Matrix &Matrix::minus(const Matrix &v) {
    int myDataSize = this->getDataSize();
    int vDataSize = v.getDataSize();
    if (myDataSize != vDataSize) {
        throw invalid_argument("array shape should be same!!");
    }
    for (int i = 0; i < myDataSize; i++) {
        this->data[i] -= v.data[i];
    }
    return *this;
}

Matrix &Matrix::multi(const Matrix &v) {
    int myDataSize = this->getDataSize();
    int vDataSize = v.getDataSize();
    if (myDataSize != vDataSize) {
        throw invalid_argument("array shape should be same!!");
    }
    for (int i = 0; i < myDataSize; i++) {
        this->data[i] *= v.data[i];
    }
    return *this;
}

Matrix &Matrix::div(const Matrix &v) {
    int myDataSize = this->getDataSize();
    int vDataSize = v.getDataSize();
    if (myDataSize != vDataSize) {
        throw invalid_argument("array shape should be same!!");
    }
    for (int i = 0; i < myDataSize; i++) {
        this->data[i] /= v.data[i];
    }
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &v) {
    return this->add(v);
}

Matrix &Matrix::operator-=(const Matrix &v) {
    return this->minus(v);
}

Matrix &Matrix::operator*=(const Matrix &v) {
    return this->multi(v);
}

Matrix &Matrix::operator/=(const Matrix &v) {
    return this->div(v);
}

Matrix Matrix::operator+(const Matrix &v) {
    Matrix result(*this);
    result.add(v);
    return result;
}

Matrix Matrix::operator-(const Matrix &v) {
    Matrix result(*this);
    result.minus(v);
    return result;
}

Matrix Matrix::operator*(const Matrix &v) {
    Matrix result(*this);
    result.multi(v);
    return result;
}

Matrix Matrix::operator/(const Matrix &v) {
    Matrix result(*this);
    result.div(v);
    return result;
}

ostream &operator<<(ostream &out, const Matrix &m) {
    if (m.getShape() == 0) {
        out << "Empty Matrix" << endl;
    }
    out << "Matrix at Shape(";
    for (int i = 0; i < Matrix::MAX_SHAPE_SIZE; i++) {
        out << m.getShape()[i] << ", ";
    }
    out << ")" << endl;

    return out;
}
