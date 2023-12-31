#ifndef GRAPHIC_ENGINE3D_GE_SHADER_HPP
#define GRAPHIC_ENGINE3D_GE_SHADER_HPP

#include "ge_vector.hpp"

class ShaderProgram
{
public:
  ShaderProgram(const std::filesystem::path& vertexPath, const std::filesystem::path& fragPath);
  ShaderProgram(std::string&& vertexSrc, std::string&& fragmentSrc);
  ~ShaderProgram();

  void Bind();

  void UploadMat4F(const std::string& name, const Mat4& mat);

  void UploadMat4F(const std::string& name, const float* mat);

  void UploadInt(const std::string& name, i32 i);

  void UploadFloat(const std::string& name, float i);

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif
