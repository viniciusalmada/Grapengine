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
    std::filesystem::path m_path;
    u32 m_width = 0;
    u32 m_height = 0;
    u32 m_renderer_ID = 0;
  };
}

#endif // GRAPENGINE_TEXTURE_2D_HPP
