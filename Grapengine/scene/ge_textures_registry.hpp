#ifndef TEXTURES_REGISTER_HPP
#define TEXTURES_REGISTER_HPP

#include "renderer/ge_texture_2d.hpp"

namespace GE
{
  class TexturesRegistry
  {
  public:
    explicit TexturesRegistry();
    TexturesRegistry(const std::map<u32, std::string>& texturePaths);

    u32 Register(const std::filesystem::path& texturePath, bool alsoLoad);
    void RegisterAtSlot(const std::filesystem::path& texturePath, u32 slot);

    void LoadTextures();

    void BindTexture(u32 slot);

    const std::map<u32, std::string>& GetTexturesPaths() const;

    [[nodiscard]] bool operator==(const TexturesRegistry& rhs) const;

  private:
    std::map<u32, std::string> m_textures_paths;
    std::map<u32, Ptr<Texture2D>> m_textures_pointers;
    u32 m_texture_next_slot;
  };

} // GE

#endif // TEXTURES_REGISTER_HPP
