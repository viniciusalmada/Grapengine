#include "ge_texture_2d.hpp"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

Texture2D::~Texture2D()
{
  glDeleteTextures(1, &m_pimpl->renderer_ID);
}

void Texture2D::Bind(u32 slot) const
{
  glBindTextureUnit(slot, m_pimpl->renderer_ID);
}
