#ifndef GE_TEXTURES_REGISTRY_SERIALIZER_HPP
#define GE_TEXTURES_REGISTRY_SERIALIZER_HPP
#include "scene/ge_textures_registry.hpp"

#include <yaml-cpp/emitter.h>

namespace GE
{
  class TexturesRegistrySerializer
  {
  public:
    TexturesRegistrySerializer(const TexturesRegistry&);

    void Serialize(YAML::Emitter& e) const;

  private:
    const TexturesRegistry& m_tex_registry;
  };

  class TexturesRegistryDeserializer
  {
  public:
    TexturesRegistryDeserializer(TexturesRegistry&);

    void Deserialize(const YAML::Node& e);

  private:
    TexturesRegistry& m_tex_registry;
  };
} // GE

#endif // TEXTURES_REGISTRY_SERIALIZER_HPP
