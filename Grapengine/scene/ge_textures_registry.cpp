#include "ge_textures_registry.hpp"

#include "core/ge_context.hpp"
#include "profiling/ge_profiler.hpp"

using namespace GE;

TexturesRegistry::TexturesRegistry() : m_texture_next_slot(1)
{
  m_textures_pointers.emplace(Texture2D::EMPTY_TEX_SLOT, nullptr);
  m_textures_paths.emplace(Texture2D::EMPTY_TEX_SLOT, "");
}

TexturesRegistry::TexturesRegistry(const std::map<u32, std::string>& texturePaths) :
    TexturesRegistry()
{
  for (const auto& [slot, tex_path] : texturePaths)
  {
    m_textures_pointers.emplace(slot, nullptr);
    m_textures_paths.emplace(slot, tex_path);
    if (slot > m_texture_next_slot)
      m_texture_next_slot = slot;
  }
  m_texture_next_slot++;
}

u32 TexturesRegistry::Register(const std::filesystem::path& texturePath, bool alsoLoad)
{
  GE_PROFILE;
  Ptr<Texture2D> tex = nullptr;
  if (alsoLoad)
  {
    tex = Texture2D::Make(texturePath);
    GE_ASSERT(tex != nullptr, "Failed to load texture: {}", texturePath.string());
  }
  u32 texture_slot = m_texture_next_slot++;
  GE_ASSERT(!m_textures_paths.contains(texture_slot), "Texture already exists: {}", texture_slot);
  m_textures_pointers.emplace(texture_slot, tex);
  m_textures_paths.emplace(texture_slot, texturePath.string());
  return texture_slot;
}

void TexturesRegistry::RegisterAtSlot(const std::filesystem::path& texturePath, u32 slot)
{
  GE_PROFILE;
  GE_ASSERT(!m_textures_paths.contains(slot), "Texture already exists: {}", slot);

  m_textures_pointers.emplace(slot, nullptr);
  m_textures_paths.emplace(slot, texturePath.string());

  m_texture_next_slot = std::ranges::max(m_textures_pointers | std::views::keys) + 1;
}

void TexturesRegistry::LoadTextures()
{
  for (const auto& [slot, tex_path] : m_textures_paths)
  {
    if (m_textures_pointers.contains(slot) && m_textures_pointers.at(slot) != nullptr)
      continue;

    if (slot == Texture2D::EMPTY_TEX_SLOT)
    {
      m_textures_pointers.at(slot) = Texture2D::Make();
      continue;
    }

    auto tex = Texture2D::Make(tex_path);
    m_textures_pointers.at(slot) = tex;
  }
}

void TexturesRegistry::BindTexture(u32 slot)
{
  GE_ASSERT(m_textures_pointers.contains(slot), "Texture not found at slot {}", slot);
  GE_ASSERT(m_textures_pointers.at(slot) != nullptr, "Texture {} is null", slot);

  const auto& tex = m_textures_pointers.at(slot);
  tex->Bind(slot);
}

const std::map<u32, std::string>& TexturesRegistry::GetTexturesPaths() const
{
  return m_textures_paths;
}

bool TexturesRegistry::operator==(const TexturesRegistry& rhs) const
{
  return m_textures_paths == rhs.m_textures_paths && m_texture_next_slot == rhs.m_texture_next_slot;
}
