#ifndef GRAPENGINE_TEXTURE_2D_HPP
#define GRAPENGINE_TEXTURE_2D_HPP

#include <filesystem>

namespace GE
{
  class Texture2D
  {
  public:
    static Ref<Texture2D> Make();

    explicit Texture2D();
    explicit Texture2D(const std::filesystem::path& path);
    ~Texture2D();

    void Bind(u32 slot) const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_TEXTURE_2D_HPP
