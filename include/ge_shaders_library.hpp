#ifndef GRAPHIC_ENGINE3D_GE_SHADERS_LIBRARY_HPP
#define GRAPHIC_ENGINE3D_GE_SHADERS_LIBRARY_HPP

class ShadersLibrary
{
public:
  static ShadersLibrary& Get();

  ShadersLibrary(const ShadersLibrary&) = delete;
  ShadersLibrary operator=(const ShadersLibrary&) = delete;

private:
  ShadersLibrary();

  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif // GRAPHIC_ENGINE3D_GE_SHADERS_LIBRARY_HPP
