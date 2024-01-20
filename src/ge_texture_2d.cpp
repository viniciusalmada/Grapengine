#include "renderer/ge_texture_2d.hpp"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <core/ge_assert.hpp>
#include <stb_image.h>

using namespace GE;

struct Texture2D::Impl
{
  std::filesystem::path path;
  u32 width = 0;
  u32 height = 0;
  u32 renderer_ID = 0;
};

Texture2D::Texture2D(const std::filesystem::path& path) : m_pimpl(MakeScope<Impl>())
{
  stbi_uc* data;
  stbi_set_flip_vertically_on_load(true);
  i32 w{}, h{}, channels{};
  data = stbi_load(path.string().c_str(), &w, &h, &channels, 0);

  m_pimpl->width = w;
  m_pimpl->height = h;

  i32 internal_format = 0;
  u32 format = 0;
  if (channels == 4)
  {
    internal_format = GL_RGBA8;
    format = GL_RGBA;
  }
  else if (channels)
  {
    internal_format = GL_RGB8;
    format = GL_RGB;
  }

  glCreateTextures(GL_TEXTURE_2D, 1, &m_pimpl->renderer_ID);
  glTextureStorage2D(m_pimpl->renderer_ID, 1, internal_format, w, h);

  glTextureParameteri(m_pimpl->renderer_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(m_pimpl->renderer_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTextureParameteri(m_pimpl->renderer_ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTextureParameteri(m_pimpl->renderer_ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  glTextureSubImage2D(m_pimpl->renderer_ID, 0, 0, 0, w, h, format, GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

Texture2D::Texture2D() : m_pimpl(MakeScope<Impl>())
{
  uint32_t internal_format = GL_RGBA8;
  uint32_t format = GL_RGBA;

  constexpr auto size = sizeof(u32);
  constexpr auto width = 1;
  constexpr auto height = 1;
  bool size_check = size == width * height * 4;
  Assert(size_check, "Error at texture size!");

  glCreateTextures(GL_TEXTURE_2D, 1, &m_pimpl->renderer_ID);
  glTextureStorage2D(m_pimpl->renderer_ID, 1, internal_format, width, height);

  glTextureParameteri(m_pimpl->renderer_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(m_pimpl->renderer_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureParameteri(m_pimpl->renderer_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(m_pimpl->renderer_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

  constexpr u32 data[] = { 0xFF'FF'FF'FF };
  glTextureSubImage2D(m_pimpl->renderer_ID, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
}

Texture2D::~Texture2D()
{
  glDeleteTextures(1, &m_pimpl->renderer_ID);
}

void Texture2D::Bind(u32 slot) const
{
  glBindTextureUnit(slot, m_pimpl->renderer_ID);
}
