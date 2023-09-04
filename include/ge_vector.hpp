#ifndef GRAPHIC_ENGINE3D_GE_VECTOR_HPP
#define GRAPHIC_ENGINE3D_GE_VECTOR_HPP

struct Vec3
{
  float x;
  float y;
  float z;

  Vec3 operator-(const Vec3& other) const;
  Vec3& operator-();
  [[nodiscard]] Vec3 Normalize() const;
  [[nodiscard]] Vec3 Cross(const Vec3& other) const;
  [[nodiscard]] float Dot(const Vec3& other) const;
};

struct Vec4
{
  float x0;
  float x1;
  float x2;
  float x3;
};

class Mat4
{
public:
  Mat4();

  Mat4(const std::array<float, 4>& row0,
       const std::array<float, 4>& row1,
       const std::array<float, 4>& row2,
       const std::array<float, 4>& row3);

  Mat4 operator*(const Mat4& other) const;

  float& operator()(unsigned int i, unsigned int j);
  const float& operator()(unsigned int i, unsigned int j) const;

  [[nodiscard]] const float* ValuePtr() const;

private:
  std::array<std::array<float, 4>, 4> data{ 0.0f };
};

#endif
