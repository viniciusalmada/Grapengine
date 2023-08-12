#include "ge_vector.hpp"

#include <gtest/gtest.h>

TEST(Vector, Mat4Multiply)
{
  Mat4<float> m1{ {
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 },
    { 13, 14, 15, 16 },
  } };

  Mat4<float> m2 = m1;

  auto prod = m1 * m2;

  ASSERT_EQ(prod[0][0], 90);
  ASSERT_EQ(prod[0][1], 100);
  ASSERT_EQ(prod[0][2], 110);
  ASSERT_EQ(prod[0][3], 120);

  ASSERT_EQ(prod[1][0], 202);
  ASSERT_EQ(prod[1][1], 228);
  ASSERT_EQ(prod[1][2], 254);
  ASSERT_EQ(prod[1][3], 280);

  ASSERT_EQ(prod[2][0], 314);
  ASSERT_EQ(prod[2][1], 356);
  ASSERT_EQ(prod[2][2], 398);
  ASSERT_EQ(prod[2][3], 440);

  ASSERT_EQ(prod[3][0], 426);
  ASSERT_EQ(prod[3][1], 484);
  ASSERT_EQ(prod[3][2], 542);
  ASSERT_EQ(prod[3][3], 600);
}
