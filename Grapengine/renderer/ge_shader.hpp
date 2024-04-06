#ifndef GRAPENGINE_SHADER_HPP
#define GRAPENGINE_SHADER_HPP

#include "math/ge_vector.hpp"

#include <filesystem>
namespace GE
{
  class Shader
  {
  public:
    static Ref<Shader> Make(const std::filesystem::path& vertexPath,
                            const std::filesystem::path& fragPath);

    Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragPath);
    GE3D Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    GE3D ~Shader();

    GE3D [[nodiscard]] bool IsValid() const;
    GE3D [[nodiscard]] bool IsBound() const;

    void Bind();
    GE3D void Unbind() const;

    void UploadMat4F(const std::string& name, const Mat4& mat);

    void UploadMat4F(const std::string& name, const f32* mat);

    void UploadInt(const std::string& name, i32 i);

    void UploadFloat(const std::string& name, f32 i);

    void UploadVec3(const std::string& name, const Vec3& vec3);

    void UploadVec3Array(const std::string& name, const std::vector<Vec3>& vec3);
    void UploadFloatArray(const std::string& name, const std::vector<f32>& vec3);

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif
