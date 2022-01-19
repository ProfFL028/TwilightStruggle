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
  
  int cst = 1;
  LArray* nums = LArray::constant(cst, ARRAY_SIZE, "Twos");
  for (int i = 0; i < ARRAY_SIZE; i++) {
    EXPECT_EQ(cst, nums->getDatas()[i]);
  }
}
