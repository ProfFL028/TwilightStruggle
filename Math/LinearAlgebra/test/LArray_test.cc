#include <gtest/gtest.h>
#include <iostream>
#include "LArray.h"

using namespace std;
using namespace la;

// Demonstrate some basic assertions.
TEST(LArray_test, BasicAssertions) {
  const int ARRAY_SIZE = 100;
  double* testData = new double[ARRAY_SIZE];
  memset(testData, 0, ARRAY_SIZE);
  const char* columnName = "test_column";

  LArray arr(testData, ARRAY_SIZE, columnName);

  EXPECT_STREQ("test_column", arr.getColumnName());
}

TEST(LArray_test, FactoryTest) {
  const int ARRAY_SIZE = 10;
  
  int cst = 5;
  LArray* nums = LArray::constant(cst, ARRAY_SIZE, "Twos");
  for (int i = 0; i < ARRAY_SIZE; i++) {
    EXPECT_EQ(cst, nums->getDatas()[i]);
  }
}

TEST(LArray_test, OperatorTest) {
    const int ARRAY_SIZE = 10;
    LArray* ones =  LArray::ones(ARRAY_SIZE);

    int cst = 3;
    ones->add(cst);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(cst + 1, ones->getDatas()[i]);
    }

    ones->minus(cst);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones->getDatas()[i]);
    }

    ones->multi(cst);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(cst, ones->getDatas()[i]);
    }

    ones->div(cst);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, ones->getDatas()[i]);
    }
}

TEST(LArray_test, OperatorOverrideTest) {
    const int ARRAY_SIZE = 10;
    LArray* ones =  LArray::ones(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(1, (*ones)[i]);
    }

    LArray cpOnes(*ones);
    EXPECT_NE(ones->getDatas(), cpOnes.getDatas());

    const int ARRAY_SIZE_HALF = ARRAY_SIZE / 2;
    LArray* twos = LArray::constant(2, ARRAY_SIZE_HALF);
    LArray three = (*ones) + (*twos);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        EXPECT_EQ(3, three[i]);
    }
}

