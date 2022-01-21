
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

void Matrix::setData(double *data, const short *shape) {
    this->clean();

    this->copyShape(shape);
    this->data = data;
    this->dataOwner = false;
}

int Matrix::getDataSize() {
    int dataSize = 1;
    for (int i = 0; i < MAX_SHAPE_SIZE; i++) {
        if (shape[i] > 0) {
            dataSize *= shape[i];
        } else {
            break;
        }
    }
    return dataSize;
}

void Matrix::copyData(const double *data, const short *shape) {
    this->clean();

    this->copyShape(shape);
    int dataSize = this->getDataSize();
    this->data = new double[dataSize];
    memcpy(this->data, data, dataSize * sizeof(double));
    this->dataOwner = true;
}

void Matrix::copyShape(const short *shape) {
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

double *Matrix::getData() {
    return this->data;
}

short *Matrix::getShape() {
    return this->shape;
}