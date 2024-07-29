#include "ge_scene_serializer.hpp"

#include "drawables/ge_mesh.hpp"
#include "ge_components_serializer.hpp"
#include "ge_serializer_constants.hpp"
#include "utils/ge_io.hpp"

#include <yaml-cpp/yaml.h>

using namespace GE;

SceneSerializer::SceneSerializer(const Ptr<Scene>& scene) : m_scene(scene) {}

std::string SceneSerializer::Serialize() const
{
  GE_ASSERT(m_scene != nullptr, "Invalid scene");

  YAML::Emitter out;
  out.SetIndent(0);
  out << YAML::BeginMap; // Main node
  out << YAML::Key << Constants::SERIALIZE_TITLE;
  out << YAML::BeginMap; // Scene node
  out << YAML::Key << Constants::NAME;
  out << YAML::Value << m_scene->GetName();
  out << YAML::Key << Constants::ENTITIES;
  out << YAML::Value << YAML::BeginSeq;

  m_scene->EachEntity(
    [&](Entity ent)
    {
      out << YAML::BeginMap; // Entity node
      out << YAML::Key << Constants::ENTITY_ID << YAML::Value << ent.handle;
      const std::vector<VarComponent>& comps = m_scene->GetComponents(ent);
      for (const VarComponent& c : comps)
      {
        std::visit<void>(ComponentSerializer(out), c);
        GE_ASSERT_NO_MSG(out.good());
      }
      out << YAML::EndMap; // Entity node
    });

  out << YAML::EndSeq;
  out << YAML::EndMap; // Scene node
  out << YAML::EndMap; // Main node

  return out.c_str();
}

void SceneSerializer::SerializeToFile(const std::filesystem::path& path) const
{
  GE_ASSERT(m_scene != nullptr, "Invalid scene");

  std::string scene_serialized = Serialize();
  std::ofstream out(path);
  out << scene_serialized;
}

void SceneSerializer::Deserialize(const std::string& sceneString)
{
  GE_ASSERT(m_scene != nullptr, "Invalid scene");
  YAML::Node config = YAML::Load(sceneString);

  YAML::Node root_node = config[Constants::SERIALIZE_TITLE];
  if (!root_node)
    return;

  YAML::Node scene_name_node = root_node[Constants::NAME];
  const std::string scene_name = scene_name_node.as<std::string>();
  m_scene->SetName(scene_name);

  YAML::Node entities_node = root_node[Constants::ENTITIES];

  for (const auto& ent_node : entities_node)
  {
    u32 ent_handle = ent_node[Constants::ENTITY_ID].as<u32>();
    Entity ent{ ent_handle };
    m_scene->PushEntity(ent);

    auto deserializer = ComponentDeserializer(ent_node);
    m_scene->PushComponent<TagComponent>(ent, deserializer.GetTag());
    m_scene->PushComponent<PrimitiveComponent>(ent, deserializer.GetPrimitive());
    m_scene->PushComponent<TransformComponent>(ent, deserializer.GetTransform());
    m_scene->PushComponent<CameraComponent>(ent, deserializer.GetCamera());
    m_scene->PushComponent<AmbientLightComponent>(ent, deserializer.GetAmbientLight());
    m_scene->PushComponent<LightSourceComponent>(ent, deserializer.GetLightSource());
  }
}

void SceneSerializer::DeserializeFromFile(const std::filesystem::path& path)
{
  GE_ASSERT(m_scene != nullptr, "Invalid scene");

  std::ifstream file(path);
  if (!file.is_open())
    return;

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string str = buffer.str();
  Deserialize(str);
}
