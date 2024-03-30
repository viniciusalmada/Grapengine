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

    [[maybe_unused]] GE3D bool IsValid() const;
    [[maybe_unused]] GE3D bool IsBound() const;

    void Bind();
    GE3D void Unbind();

    void UploadMat4F(const std::string& name, const Mat4& mat);

    void UploadMat4F(const std::string& name, const f32* mat);

    void UploadInt(const std::string& name, i32 i);

    void UploadFloat(const std::string& name, f32 i);

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}
#endif
