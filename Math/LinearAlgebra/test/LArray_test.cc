#include <gtest/gtest.h>
#include <iostream>
#include "LArray.h"

using namespace std;
using namespace la;

TEST(LArray_test, PropertyTest) {
    // test empty array.
    LArray empty;
    EXPECT_EQ(empty.getDatas(), nullptr);
    EXPECT_EQ(empty.getColumnName(), nullptr);
    EXPECT_EQ(empty.getLength(), 0);

    const int ARRAY_SIZE = 100;
    double* testData = new double[ARRAY_SIZE];
    memset(testData, 0, ARRAY_SIZE);
    const char* columnName = "test_column";

    LArray arr(testData, ARRAY_SIZE, columnName);
    EXPECT_STREQ("test_column", arr.getColumnName());
    EXPECT_EQ(arr.getDatas(), testData);
    
    LArray arr2;
    arr2.setDatas(testData, ARRAY_SIZE);
    EXPECT_EQ(arr2.getDatas(), testData);
    
    arr2.getDatas()[2] = 5;
    EXPECT_EQ(5, testData[2]);
}

TEST(LArray_test, FactoryTest) {
  const int ARRAY_SIZE = 10;
  
  int cst = 5;

  LArray* nums = LArray::constant(cst, ARRAY_SIZE, "Fives");
  for (int i = 0; i < ARRAY_SIZE; i++) {
    EXPECT_EQ(cst, nums->getDatas()[i]);
  }
}

TEST(LArray_test, OperatorWithDoubleTest) {
    const int ARRAY_SIZE = 10;
    LArray ones =  *(LArray::ones(ARRAY_SIZE));

    int cst = 3;
    ones.add(cst);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(cst + 1, ones[i]);
    }

    ones.minus(cst);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones[i]);
    }

    ones.multi(cst);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(cst, ones[i]);
    }

    ones.div(cst);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones[i]);
    }

    LArray tmp = ones + 3;
    EXPECT_NE(ones.getDatas(), tmp.getDatas());
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones[i]);
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(4, tmp[i]);
    }
    tmp = tmp - 3;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, tmp[i]);
    }
    tmp = tmp * 3;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(3, tmp[i]);
    }
    tmp = tmp / 3;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, tmp[i]);
    }

    ones += 3;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(4, ones[i]);
    }
    ones -= 3;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones[i]);
    }
    ones *= 3;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(3, ones[i]);
    }
    ones /= 3;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones[i]);
    }
}

TEST(LArray_test, OperatorOverrideTest) {
    const int ARRAY_SIZE = 10;
    LArray ones =  *LArray::ones(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones[i]);
    }

    LArray cpOnes(ones);
    EXPECT_NE(ones.getDatas(), cpOnes.getDatas());

    const int ARRAY_SIZE_HALF = ARRAY_SIZE / 2;
    LArray twos = *LArray::constant(2, ARRAY_SIZE_HALF);
    LArray threes = ones + twos;
    EXPECT_NE(ones.getDatas(), threes.getDatas());
    EXPECT_NE(twos.getDatas(), threes.getDatas());
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(3, threes[i]);
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones[i]);
    }
    for (int i = 0; i < ARRAY_SIZE_HALF; i++) {
        EXPECT_EQ(2, twos[i]);
    }

    LArray newOnes = threes - twos;
    EXPECT_NE(threes.getDatas(), newOnes.getDatas());
    EXPECT_NE(twos.getDatas(), newOnes.getDatas());
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, newOnes[i]);
    }

    LArray fours = twos * twos;
    EXPECT_NE(fours.getDatas(), twos.getDatas());
    for (int i = 0; i < ARRAY_SIZE_HALF; i++) {
        EXPECT_EQ(4, fours[i]);
        EXPECT_EQ(2, twos[i]);
    }

    EXPECT_EQ(ARRAY_SIZE, threes.getLength());
    EXPECT_EQ(ARRAY_SIZE_HALF, twos.getLength());
    EXPECT_EQ(ARRAY_SIZE, ones.getLength());
    
    ones += twos;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(3, ones[i]);
    }

    ones -= twos;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones[i]);
    }

    ones *= twos;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(2, ones[i]);
    }

    ones /= twos;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones[i]);
    }
}

