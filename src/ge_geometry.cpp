#include "math/ge_geometry.hpp"

#include "math/ge_transformations.hpp"

f32 GE::Geom::AngleBetween(const GE::Vec3& a, const GE::Vec3& b)
{
  // Calculate the dot product of vectors a and b
  f32 dotProduct = a.Dot(b);

  // Calculate the magnitudes of vectors a and b
  f32 magA = a.Length();
  f32 magB = b.Length();

  // Calculate the cosine of the angle between the vectors
  f32 cosineAngle = dotProduct / (magA * magB);

  // Clamp the value to the range [-1, 1] to avoid numerical errors
  cosineAngle = std::clamp(cosineAngle, -1.0f, 1.0f);

  // Calculate the angle in radians using the arccosine function
  f32 angleRadians = std::acos(cosineAngle);

  // Convert the angle from radians to degrees
  f32 angleDegrees = Transform::Rad2Deg(angleRadians);

  return angleDegrees;
}
