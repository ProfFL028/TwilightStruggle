#include <gtest/gtest.h>
#include <iostream>
#include "LArray.h"

using namespace std;
// Demonstrate some basic assertions.
TEST(LArray_test, BasicAssertions) {
  const int ARRAY_SIZE = 100;
  double* test_data = new double[ARRAY_SIZE];
  memset(test_data, 0, ARRAY_SIZE);
  const char* column_name = "test_column";

  LArray arr(test_data, ARRAY_SIZE, column_name);

  EXPECT_STREQ("test_column", arr.getColumnName());
}
