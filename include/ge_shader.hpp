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

  void UploadInt(const std::string& name, int i);

private:
  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif
