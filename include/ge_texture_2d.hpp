#ifndef GRAPHIC_ENGINE3D_GE_TEXTURE_2D_HPP
#define GRAPHIC_ENGINE3D_GE_TEXTURE_2D_HPP

class Texture2D
{
public:
  explicit Texture2D(const std::filesystem::path& path);
  ~Texture2D();

  void Bind(uint32_t slot) const;

private:
  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif // GRAPHIC_ENGINE3D_GE_TEXTURE_2D_HPP
