#include "renderer/ge_shaders_library.hpp"

#include "renderer/ge_shader.hpp"

struct ShadersLibrary::Impl
{
  std::list<Ref<ShaderProgram>> shaders;
};

ShadersLibrary& ShadersLibrary::Get()
{
  static ShadersLibrary self{};
  return self;
}

ShadersLibrary::ShadersLibrary() : m_pimpl(MakeScope<Impl>()) {}
