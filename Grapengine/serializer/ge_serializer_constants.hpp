#ifndef GE_SERIALIZER_CONSTANTS_HPP
#define GE_SERIALIZER_CONSTANTS_HPP

namespace GE
{
  namespace Constants
  {
    constexpr auto SERIALIZE_TITLE = "Grapengine Scene";
    constexpr auto NAME = "Name";
    constexpr auto ENTITIES = "Entities";
    constexpr auto ENTITY_ID = "EntityID";
  }

  namespace Titles
  {
    constexpr auto TAG_COMP = "TagComponent";
    constexpr auto TRANFORM_COMP = "TransformComponent";
    constexpr auto PRIMITIVE_COMP = "PrimitiveComponent";
    constexpr auto CAMERA_COMP = "CameraComponent";
    // constexpr auto NATIVE_SCRIPT_COMP = "NativeScriptComponent";
    constexpr auto AMBIENT_LIGHT_COMP = "AmbientLightComponent";
    constexpr auto LIGHT_SOURCE_COMP = "LightSourceComponent";
  }

  namespace Fields
  {
    constexpr auto TAG = "Tag";
    constexpr auto POSITION = "Position";
    constexpr auto ROTATION = "Rotation";
    constexpr auto SCALE = "Scale";
    constexpr auto DRAWABLE = "Drawable";
    constexpr auto VERTICES_COUNT = "VerticesCount";
    constexpr auto VERTICES_DATA = "VerticesData";
    constexpr auto TEX_COORDINATES = "TextureCoordinates";
    constexpr auto COLOR_RGBA = "ColorRGBA";
    constexpr auto RGB = "RGB";
    constexpr auto ALPHA = "Alpha";
    constexpr auto COLOR_DECIMAL = "ColorDecimal";
    constexpr auto NORMAL = "Normal";
    constexpr auto INDICES_DATA = "IndicesData";
    constexpr auto SCENE_CAMERA = "SceneCamera";
    constexpr auto CAMERA = "Camera";
    constexpr auto PROJECTION = "Projection";
    constexpr auto TARGET = "Target";
    constexpr auto VIEWPORT = "Viewport";
    constexpr auto FOV = "Fov";
    constexpr auto ORTHO_SIZE = "OrthoSize";
    constexpr auto PROJECTION_MODE = "ProjectionMode";
    constexpr auto ACTIVE = "Active";
    constexpr auto FIXED_RATIO = "FixedRatio";
    constexpr auto STRENGHT = "Strenght";
    constexpr auto SPEC_STRENGHT = "SpecularStrenght";
    constexpr auto SPEC_SHINE = "SpecularShininess";
    constexpr auto LIGHT_SOURCE = "LightSource";
  }
}
#endif // GE_SERIALIZER_CONSTANTS_HPP
