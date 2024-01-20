#ifndef GRAPHIC_ENGINE3D_GE_TEXTURE_2D_HPP
#define GRAPHIC_ENGINE3D_GE_TEXTURE_2D_HPP

class Texture2D
{
public:
  explicit Texture2D();
  explicit Texture2D(const std::filesystem::path& path);
  ~Texture2D();

  void Bind(u32 slot) const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif // GRAPHIC_ENGINE3D_GE_TEXTURE_2D_HPP
