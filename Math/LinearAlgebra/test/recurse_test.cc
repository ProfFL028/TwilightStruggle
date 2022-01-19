#include <gtest/gtest.h>

#include "Linear.h"
#include "Matrix.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);

  EXPECT_GE(10, 1);
  
  Linear linear;
  linear.a = 100;
  
  Matrix matrix;
  
}