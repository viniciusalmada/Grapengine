#ifndef GE_COMPONENTS_SERIALIZER_HPP
#define GE_COMPONENTS_SERIALIZER_HPP

#include "scene/ge_components.hpp"

#include <yaml-cpp/yaml.h>

namespace GE
{
  class ComponentSerializer
  {
  public:
    explicit ComponentSerializer(YAML::Emitter& emmiter);

    void operator()(const TagComponent& c) const;
    void operator()(const TransformComponent& c) const;
    void operator()(const PrimitiveComponent& c) const;
    void operator()(const CameraComponent& c) const;
    void operator()(const NativeScriptComponent& c) const;
    void operator()(const AmbientLightComponent& c) const;
    void operator()(const LightSourceComponent& c) const;

  private:
    YAML::Emitter& m_emitter;
  };

  class ComponentDeserializer
  {
  public:
    explicit ComponentDeserializer(const YAML::Node& it);

    Opt<TagComponent> GetTag() const;
    Opt<TransformComponent> GetTransform() const;
    Opt<PrimitiveComponent> GetPrimitive() const;
    Opt<CameraComponent> GetCamera() const;
    Opt<NativeScriptComponent> GetNativeScript() const;
    Opt<AmbientLightComponent> GetAmbientLight() const;
    Opt<LightSourceComponent> GetLightSource() const;

  private:
    const YAML::Node& m_node;
  };
} // GE

#endif // GE_COMPONENTS_SERIALIZER_HPP
