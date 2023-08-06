#ifndef GRAPHIC_ENGINE3D_GE_SHADER_HPP
#define GRAPHIC_ENGINE3D_GE_SHADER_HPP

class Shader
{
public:
  Shader(std::string&& vertexSrc, std::string&& fragmentSrc);
  ~Shader();

  void Bind();

private:
  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif
