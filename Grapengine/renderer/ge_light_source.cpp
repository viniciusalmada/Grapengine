#include "ge_light_source.hpp"

#include "math/ge_arithmetic.hpp"

bool GE::LightSource::operator==(const LightSource& other) const
{
  return position == other.position &&                            //
         color == other.color &&                                  //
         Arithmetic::IsEqual(light_str, other.light_str) &&       //
         Arithmetic::IsEqual(specular_str, other.specular_str) && //
         shininess == other.shininess;
}
