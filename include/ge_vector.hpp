#ifndef GRAPHIC_ENGINE3D_GE_VECTOR_HPP
#define GRAPHIC_ENGINE3D_GE_VECTOR_HPP

using Vec3 = std::tuple<float, float, float>;
using Vec4 = std::tuple<float, float, float, float>;

Vec3 operator-(const Vec3& v1, const Vec3& v2);
Vec3& operator-(Vec3& v);
Vec3 Normalize(const Vec3& v);
Vec3 Cross(const Vec3& v1, const Vec3& v2);
float Dot(const Vec3& v1, const Vec3& v2);

template <typename T> // Mat[row][column]
using Mat4 = std::array<std::array<T, 4>, 4>;

template <typename T> // Mat[row][column]
inline Mat4<T> operator*(const Mat4<T>& m1, const Mat4<T>& m2)
{
  auto prod = [&m1, &m2](unsigned int r, unsigned c)
  { return m1[r][0] * m2[0][c] + m1[r][1] * m2[1][c] + m1[r][2] * m2[2][c] + m1[r][3] * m2[3][c]; };

  Mat4<T> res;
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      res[i][j] = prod(i, j);
    }
  }

  return res;
}

#endif
