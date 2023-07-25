#ifndef GRAPHICENGINE3D_GE_SHADER_HPP
#define GRAPHICENGINE3D_GE_SHADER_HPP

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

#endif // GRAPHICENGINE3D_GE_SHADER_HPP
