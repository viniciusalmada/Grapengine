#include "renderer/ge_shaders_library.hpp"

#include "renderer/ge_buffer_layout.hpp"

#include <core/ge_assert.hpp>
#include <renderer/ge_ishader_program.hpp>
#include <renderer/shader_programs/ge_pos_tex_shader.hpp>

using namespace GE;

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

GE::Ref<BufferLayout> GE::ShadersLibrary::GetLayout(Shaders shader) const
{
  switch (shader)
  {
  case Shaders::POSITION_AND_TEXTURE2D:
    return MakeRef<BufferLayout>(BufferLayout::BuildElementsList({ //
                                                                   ShaderDataType::Float3,
                                                                   ShaderDataType::Float2,
                                                                   ShaderDataType::Float4 }));
  }
  return nullptr;
}
