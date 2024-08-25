#include "ge_textures_registry_serializer.hpp"

#include "ge_serializer_constants.hpp"
#include "profiling/ge_profiler.hpp"

#include <yaml-cpp/yaml.h>

using namespace GE;

TexturesRegistrySerializer::TexturesRegistrySerializer(const TexturesRegistry& registry) :
    m_tex_registry(registry)
{
}

void TexturesRegistrySerializer::Serialize(YAML::Emitter& e) const
{
  e << YAML::BeginSeq;
  const std::map<u32, std::string>& paths = m_tex_registry.GetTexturesPaths();
  for (const auto& [slot, path] : paths)
  {
    e << YAML::BeginMap;
    e << YAML::Key << Fields::TEXTURE_SLOT << YAML::Value << slot;
    e << YAML::Key << Fields::TEXTURE_PATH << YAML::Value << path;
    e << YAML::EndMap;
  }
  e << YAML::EndSeq;
}

TexturesRegistryDeserializer::TexturesRegistryDeserializer(TexturesRegistry& reg) :
    m_tex_registry(reg)
{
}

void TexturesRegistryDeserializer::Deserialize(const YAML::Node& e)
{
  GE_PROFILE;

  GE_ASSERT(e.IsSequence(), "YAML node invalid for textures");

  for (const auto& tex_node : e)
  {
    const u32 slot = tex_node[Fields::TEXTURE_SLOT].as<u32>();
    if (slot == Texture2D::EMPTY_TEX_SLOT)
      continue;
    const std::string path = tex_node[Fields::TEXTURE_PATH].as<std::string>();
    m_tex_registry.RegisterAtSlot({ path }, slot);
  }
}
