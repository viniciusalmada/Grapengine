#ifndef GRAPENGINE_SHADER_HPP
#define GRAPENGINE_SHADER_HPP

#include "math/ge_vector.hpp"

class Shader
{
public:
  Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragPath);
  GE3D Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
  GE3D ~Shader();

  [[maybe_unused]] GE3D bool IsValid() const;
  [[maybe_unused]] GE3D bool IsBound() const;

  void Bind();
  GE3D void Unbind();

  void UploadMat4F(const std::string& name, const Mat4& mat);

  void UploadMat4F(const std::string& name, const float* mat);

  void UploadInt(const std::string& name, i32 i);

  void UploadFloat(const std::string& name, float i);

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif
