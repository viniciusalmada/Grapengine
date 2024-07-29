#ifndef SCENE_SERIALIZER_HPP
#define SCENE_SERIALIZER_HPP

#include "scene/ge_scene.hpp"

namespace GE
{
  class SceneSerializer
  {
  public:
    SceneSerializer(const Ptr<Scene>& scene);

    std::string Serialize() const;
    void SerializeToFile(const std::filesystem::path& path) const;

    void Deserialize(const std::string& sceneString);
    void DeserializeFromFile(const std::filesystem::path& path);

  private:
    Ptr<Scene> m_scene;
  };

} // GE

#endif // SCENE_SERIALIZER_HPP
