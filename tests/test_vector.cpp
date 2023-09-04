#include "ge_vector.hpp"

#include <gtest/gtest.h>

TEST(Vec3, MinusOperator)
{
  Vec3 v1{ 1, 2, 3 };
  Vec3 v2{ 4, 5, 6 };
  Vec3 res = v2 - v1;

  ASSERT_EQ(res.x, 3);
  ASSERT_EQ(res.y, 3);
  ASSERT_EQ(res.z, 3);
}

TEST(Vec3, UnaryMinusOperator)
{
  Vec3 res{ 1, 2, 3 };
  -res;

  ASSERT_EQ(res.x, -1);
  ASSERT_EQ(res.y, -2);
  ASSERT_EQ(res.z, -3);
}

TEST(Vec3, Normalize)
{
  Vec3 v1{ 1, 2, 3 };
  Vec3 res = v1.Normalize();

  ASSERT_FLOAT_EQ(res.x, 0.267261241912424f);
  ASSERT_FLOAT_EQ(res.y, 0.534522483824849f);
  ASSERT_FLOAT_EQ(res.z, 0.801783725737273f);
}

TEST(Vec3, Cross)
{
  Vec3 v1{ 1, 2, 3 };
  Vec3 v2{ 4, 5, 6 };
  Vec3 res = v1.Cross(v2);

  ASSERT_EQ(res.x, -3);
  ASSERT_EQ(res.y, 6);
  ASSERT_EQ(res.z, -3);
}

TEST(Vec3, Dot)
{
  Vec3 v1{ 1, 2, 3 };
  Vec3 v2{ 4, 5, 6 };
  float res = v1.Dot(v2);

  ASSERT_FLOAT_EQ(res, 32);
}

TEST(Vector, Mat4Multiply)
{
  Mat4 m1{
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 },
    { 13, 14, 15, 16 },
  };

  Mat4 m2 = m1;

  auto prod = m1 * m2;

  ASSERT_EQ(prod(0, 0), 90);
  ASSERT_EQ(prod(0, 1), 100);
  ASSERT_EQ(prod(0, 2), 110);
  ASSERT_EQ(prod(0, 3), 120);

  ASSERT_EQ(prod(1, 0), 202);
  ASSERT_EQ(prod(1, 1), 228);
  ASSERT_EQ(prod(1, 2), 254);
  ASSERT_EQ(prod(1, 3), 280);

  ASSERT_EQ(prod(2, 0), 314);
  ASSERT_EQ(prod(2, 1), 356);
  ASSERT_EQ(prod(2, 2), 398);
  ASSERT_EQ(prod(2, 3), 440);

  ASSERT_EQ(prod(3, 0), 426);
  ASSERT_EQ(prod(3, 1), 484);
  ASSERT_EQ(prod(3, 2), 542);
  ASSERT_EQ(prod(3, 3), 600);
}
