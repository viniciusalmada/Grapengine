#ifndef GRAPENGINE_SHADER_HPP
#define GRAPENGINE_SHADER_HPP

#include "ge_renderer_id.hpp"
#include "math/ge_vector.hpp"

#include <filesystem>
namespace GE
{
  class Shader
  {
  public:
    static Ptr<Shader> Make(const std::filesystem::path& vertexPath,
                            const std::filesystem::path& fragPath);

    Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragPath);
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    [[nodiscard]] bool IsValid() const;
    [[nodiscard]] bool IsBound() const;

    void Bind() const;
    void Unbind() const;

    void UploadMat4F(const std::string& name, const Mat4& mat);

    void UploadMat4F(const std::string& name, const f32* data);

    void UploadInt(const std::string& name, i32 i);

    void UploadFloat(const std::string& name, f32 i);

    void UploadVec3(const std::string& name, const Vec3& vec3);

    void UploadVec3Array(const std::string& name, const std::vector<Vec3>& vec3);
    void UploadFloatArray(const std::string& name, const std::vector<f32>& vec3);
    void UploadIntArray(const std::string& name, const std::vector<i32>& arr);

  private:
    i32 RetrieveUniform(const std::string& name);

    RendererID m_renderer_id;
    std::unordered_map<std::string, i32> m_uniforms;
  };
}
#endif
