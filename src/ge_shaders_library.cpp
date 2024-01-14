#include "renderer/ge_shaders_library.hpp"

#include <core/ge_assert.hpp>
#include <renderer/ge_ishader_program.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>

struct ShadersLibrary::Impl
{
  std::unordered_map<Shaders, Ref<IShaderProgram>> shaders;
};

ShadersLibrary& ShadersLibrary::Get()
{
  static ShadersLibrary self{};
  return self;
}

ShadersLibrary::ShadersLibrary() : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->shaders[Shaders::POSITION_AND_TEXTURE2D] = MakeRef<PosAndTex2DShader>();
}

Ref<IShaderProgram> ShadersLibrary::GetShader(Shaders shader) const
{
  Assert(m_pimpl->shaders.contains(shader), "Shader not registered");
  return m_pimpl->shaders[shader];
}

void ShadersLibrary::Activate(Shaders shader)
{
  Assert(m_pimpl->shaders.contains(shader), "Shader not registered");
  m_pimpl->shaders[shader]->Activate();
}

void ShadersLibrary::SubToResizePub(IPublisher<Vec2>& pub) const
{
  pub.Subscribe(
   std::static_pointer_cast<PosAndTex2DShader>(m_pimpl->shaders[Shaders::POSITION_AND_TEXTURE2D]));
}

void ShadersLibrary::SubToCameraPub(IPublisher<Mat4>& pub) const
{
  pub.Subscribe(
    std::static_pointer_cast<PosAndTex2DShader>(m_pimpl->shaders[Shaders::POSITION_AND_TEXTURE2D]));
}
