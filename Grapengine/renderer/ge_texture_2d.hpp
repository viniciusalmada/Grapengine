#ifndef GRAPENGINE_TEXTURE_2D_HPP
#define GRAPENGINE_TEXTURE_2D_HPP

#include "ge_renderer_id.hpp"
#include "utils/ge_dimension.hpp"

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
    Dimension m_dim;
    RendererID m_renderer_ID;
  };
}

#endif // GRAPENGINE_TEXTURE_2D_HPP
