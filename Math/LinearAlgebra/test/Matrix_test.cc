#include <gtest/gtest.h>
#include <iostream>
#include "Matrix.h"

using namespace std;
using namespace la;

TEST(Matrix_test, ConstructTest) {
    Matrix m;
    EXPECT_EQ(nullptr, m.getData());
    EXPECT_EQ(nullptr, m.getShape());

    short* shape1 = new short [5] {3, 4, 5, 1, 1};
    double* data = new double[60];
    for (int i = 0; i < 60; i++) {
        data[i] = i;
    }
    Matrix m2(data, shape1);
    EXPECT_EQ(data, m2.getData());
    EXPECT_NE(shape1, m2.getShape());
    EXPECT_EQ(3, m2.getShape()[0]);
    EXPECT_EQ(4, m2.getShape()[1]);
    EXPECT_EQ(5, m2.getShape()[2]);
    EXPECT_EQ(1, m2.getShape()[3]);
    EXPECT_EQ(1, m2.getShape()[4]);
    EXPECT_EQ(60, m2.getDataSize());

    data[33] = 100;
    EXPECT_EQ(data[33], m2.getData()[33]);

    Matrix cp(m2);
    EXPECT_NE(data, cp.getData());
    EXPECT_NE(shape1, cp.getShape());

    EXPECT_EQ(3, cp.getShape()[0]);
    EXPECT_EQ(4, cp.getShape()[1]);
    EXPECT_EQ(5, cp.getShape()[2]);
    EXPECT_EQ(1, cp.getShape()[3]);
    EXPECT_EQ(1, cp.getShape()[4]);
    EXPECT_EQ(60, cp.getDataSize());

    delete[] data;
    delete[] shape1;
}

TEST(Matrix_test, CopyTest) {
    short* shape = new short [5] {3, 4, 5, 1, 1};
    double* data = new double[60];
    for (int i = 0; i < 60; i++) {
        data[i] = i;
    }
    Matrix m(data, shape);

    for (int i = 0; i <m.getDataSize(); i++) {
        EXPECT_EQ(i, m[i]);
    }

    Matrix m2 = m;
    EXPECT_NE(&m, &m2);
    for (int i = 0; i <m.getDataSize(); i++) {
        EXPECT_EQ(m2[i], m[i]);
    }

    delete [] data;
    delete [] shape;
}

TEST(Matrix_test, DoubleOperatorTest) {
    short* shape = new short [5] {10, 5, 1, 1, 1};
    Matrix m1 = *Matrix::ones(shape);
    const int cst = 5;
    m1.add(cst);
    for (int i = 0; i <m1.getDataSize(); i++) {
        EXPECT_EQ(1 + cst, m1[i]);
    }
    m1.minus(cst);
    for (int i = 0; i <m1.getDataSize(); i++) {
        EXPECT_EQ(1, m1[i]);
    }
    m1.multi(cst);
    for (int i = 0; i <m1.getDataSize(); i++) {
        EXPECT_EQ(cst, m1[i]);
    }
    m1.div(cst);
    for (int i = 0; i <m1.getDataSize(); i++) {
        EXPECT_EQ(1, m1[i]);
    }
    m1.add(cst).minus(cst).multi(cst).div(cst);
    for (int i = 0; i <m1.getDataSize(); i++) {
        EXPECT_EQ(1, m1[i]);
    }

    cout << "following code will call constructor a lot." << endl << endl;
    m1 = m1 + cst;

    for (int i = 0; i <m1.getDataSize(); i++) {
        EXPECT_EQ(1 + cst, m1[i]);
    }
    m1 = m1 - cst;
    for (int i = 0; i <m1.getDataSize(); i++) {
        EXPECT_EQ(1, m1[i]);
    }
    m1 = m1 * cst;
    for (int i = 0; i <m1.getDataSize(); i++) {
        EXPECT_EQ(cst, m1[i]);
    }
    m1 = m1 / cst;
    for (int i = 0; i <m1.getDataSize(); i++) {
        EXPECT_EQ(1, m1[i]);
    }

}

