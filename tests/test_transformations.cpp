#include "ge_transformations.hpp"

#include <gtest/gtest.h>

TEST(Transform, Deg2Rad)
{
  float r_0 = Transform::Deg2Rad(0.0f);
  ASSERT_FLOAT_EQ(r_0, 0);

  float r_pi = Transform::Deg2Rad(180.0f);
  ASSERT_FLOAT_EQ(r_pi, std::numbers::pi_v<float>);

  float r_2pi = Transform::Deg2Rad(360.0f);
  ASSERT_FLOAT_EQ(r_2pi, 2 * std::numbers::pi_v<float>);
}

TEST(Transform, Translate)
{
  Mat4 tra = Transform::Translate(1, 2, 3);

  ASSERT_EQ(tra(0, 0), 1);
  ASSERT_EQ(tra(0, 1), 0);
  ASSERT_EQ(tra(0, 2), 0);
  ASSERT_EQ(tra(0, 3), 1);
  ASSERT_EQ(tra(1, 0), 0);
  ASSERT_EQ(tra(1, 1), 1);
  ASSERT_EQ(tra(1, 2), 0);
  ASSERT_EQ(tra(1, 3), 2);
  ASSERT_EQ(tra(2, 0), 0);
  ASSERT_EQ(tra(2, 1), 0);
  ASSERT_EQ(tra(2, 2), 1);
  ASSERT_EQ(tra(2, 3), 3);
  ASSERT_EQ(tra(3, 0), 0);
  ASSERT_EQ(tra(3, 1), 0);
  ASSERT_EQ(tra(3, 2), 0);
  ASSERT_EQ(tra(3, 3), 1);
}

TEST(Transform, RotateX)
{
  auto angle = 30.0f;
  Mat4 tra = Transform::RotateX(angle);
  auto co = std::cosf(Transform::Deg2Rad(angle));
  auto si = std::sinf(Transform::Deg2Rad(angle));

  ASSERT_FLOAT_EQ(tra(0, 0), 1);
  ASSERT_FLOAT_EQ(tra(0, 1), 0);
  ASSERT_FLOAT_EQ(tra(0, 2), 0);
  ASSERT_FLOAT_EQ(tra(0, 3), 0);
  ASSERT_FLOAT_EQ(tra(1, 0), 0);
  ASSERT_FLOAT_EQ(tra(1, 1), co);
  ASSERT_FLOAT_EQ(tra(1, 2), -si);
  ASSERT_FLOAT_EQ(tra(1, 3), 0);
  ASSERT_FLOAT_EQ(tra(2, 0), 0);
  ASSERT_FLOAT_EQ(tra(2, 1), si);
  ASSERT_FLOAT_EQ(tra(2, 2), co);
  ASSERT_FLOAT_EQ(tra(2, 3), 0);
  ASSERT_FLOAT_EQ(tra(3, 0), 0);
  ASSERT_FLOAT_EQ(tra(3, 1), 0);
  ASSERT_FLOAT_EQ(tra(3, 2), 0);
  ASSERT_FLOAT_EQ(tra(3, 3), 1);
}

TEST(Transform, RotateY)
{
  auto angle = 30.0f;
  Mat4 tra = Transform::RotateY(angle);
  auto co = std::cosf(Transform::Deg2Rad(angle));
  auto si = std::sinf(Transform::Deg2Rad(angle));

  ASSERT_FLOAT_EQ(tra(0, 0), co);
  ASSERT_FLOAT_EQ(tra(0, 1), 0);
  ASSERT_FLOAT_EQ(tra(0, 2), si);
  ASSERT_FLOAT_EQ(tra(0, 3), 0);
  ASSERT_FLOAT_EQ(tra(1, 0), 0);
  ASSERT_FLOAT_EQ(tra(1, 1), 1);
  ASSERT_FLOAT_EQ(tra(1, 2), 0);
  ASSERT_FLOAT_EQ(tra(1, 3), 0);
  ASSERT_FLOAT_EQ(tra(2, 0), -si);
  ASSERT_FLOAT_EQ(tra(2, 1), 0);
  ASSERT_FLOAT_EQ(tra(2, 2), co);
  ASSERT_FLOAT_EQ(tra(2, 3), 0);
  ASSERT_FLOAT_EQ(tra(3, 0), 0);
  ASSERT_FLOAT_EQ(tra(3, 1), 0);
  ASSERT_FLOAT_EQ(tra(3, 2), 0);
  ASSERT_FLOAT_EQ(tra(3, 3), 1);
}

TEST(Transform, RotateZ)
{
  auto angle = 30.0f;
  Mat4 tra = Transform::RotateZ(angle);
  auto co = std::cosf(Transform::Deg2Rad(angle));
  auto si = std::sinf(Transform::Deg2Rad(angle));

  ASSERT_FLOAT_EQ(tra(0, 0), co);
  ASSERT_FLOAT_EQ(tra(0, 1), -si);
  ASSERT_FLOAT_EQ(tra(0, 2), 0);
  ASSERT_FLOAT_EQ(tra(0, 3), 0);
  ASSERT_FLOAT_EQ(tra(1, 0), si);
  ASSERT_FLOAT_EQ(tra(1, 1), co);
  ASSERT_FLOAT_EQ(tra(1, 2), 0);
  ASSERT_FLOAT_EQ(tra(1, 3), 0);
  ASSERT_FLOAT_EQ(tra(2, 0), 0);
  ASSERT_FLOAT_EQ(tra(2, 1), 0);
  ASSERT_FLOAT_EQ(tra(2, 2), 1);
  ASSERT_FLOAT_EQ(tra(2, 3), 0);
  ASSERT_FLOAT_EQ(tra(3, 0), 0);
  ASSERT_FLOAT_EQ(tra(3, 1), 0);
  ASSERT_FLOAT_EQ(tra(3, 2), 0);
  ASSERT_FLOAT_EQ(tra(3, 3), 1);
}

TEST(Transform, Scale)
{
  Mat4 tra = Transform::Scale(0.1f, 0.2f, 0.3f);

  ASSERT_FLOAT_EQ(tra(0, 0), 0.1f);
  ASSERT_FLOAT_EQ(tra(0, 1), 0);
  ASSERT_FLOAT_EQ(tra(0, 2), 0);
  ASSERT_FLOAT_EQ(tra(0, 3), 0);
  ASSERT_FLOAT_EQ(tra(1, 0), 0);
  ASSERT_FLOAT_EQ(tra(1, 1), 0.2f);
  ASSERT_FLOAT_EQ(tra(1, 2), 0);
  ASSERT_FLOAT_EQ(tra(1, 3), 0);
  ASSERT_FLOAT_EQ(tra(2, 0), 0);
  ASSERT_FLOAT_EQ(tra(2, 1), 0);
  ASSERT_FLOAT_EQ(tra(2, 2), 0.3f);
  ASSERT_FLOAT_EQ(tra(2, 3), 0);
  ASSERT_FLOAT_EQ(tra(3, 0), 0);
  ASSERT_FLOAT_EQ(tra(3, 1), 0);
  ASSERT_FLOAT_EQ(tra(3, 2), 0);
  ASSERT_FLOAT_EQ(tra(3, 3), 1);
}

constexpr float DELTA = 1.0e-6f;

TEST(Transform, LookAt)
{
  Vec3 eye{ 1, 2, 3 };
  Vec3 target{ 0, 0, 0 };
  Vec3 up{ 0, 1, 0 };
  Mat4 tra = Transform::LookAt(eye, target, up);

  ASSERT_NEAR(tra(0, 0), 0.94868332, DELTA);
  ASSERT_NEAR(tra(0, 1), 0, DELTA);
  ASSERT_NEAR(tra(0, 2), -0.31622779, DELTA);
  ASSERT_NEAR(tra(0, 3), 0, DELTA);

  ASSERT_NEAR(tra(1, 0), -0.169031, DELTA);
  ASSERT_NEAR(tra(1, 1), 0.845154, DELTA);
  ASSERT_NEAR(tra(1, 2), -0.507093, DELTA);
  ASSERT_NEAR(tra(1, 3), 0, DELTA);

  ASSERT_NEAR(tra(2, 0), 0.267261, DELTA);
  ASSERT_NEAR(tra(2, 1), 0.534522, DELTA);
  ASSERT_NEAR(tra(2, 2), 0.801784, DELTA);
  ASSERT_NEAR(tra(2, 3), -3.741657, DELTA);

  ASSERT_NEAR(tra(3, 0), 0, DELTA);
  ASSERT_NEAR(tra(3, 1), 0, DELTA);
  ASSERT_NEAR(tra(3, 2), 0, DELTA);
  ASSERT_NEAR(tra(3, 3), 1.00000, DELTA);
}

  ASSERT_NEAR(tra(3, 0), 0, float(1e9));
  ASSERT_NEAR(tra(3, 1), 0, float(1e9));
  ASSERT_NEAR(tra(3, 2), 0, float(1e9));
  ASSERT_NEAR(tra(3, 3), 1.00000, float(1e9));
}
