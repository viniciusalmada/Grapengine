#include "renderer/ge_framebuffer.hpp"

#include <core/ge_assert.hpp>
#include <glad/glad.h>

using namespace GE;

namespace
{
  bool IsFramebufferBound(RendererID fb)
  {
    i32 current_fb = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &current_fb);
    const bool is_any_fb_bound = current_fb != 0;
    if (!is_any_fb_bound)
      return false;

    const bool is_fb_bound = current_fb == i32(u32(fb));

    return is_fb_bound;
  }

}

Ref<Framebuffer> Framebuffer::Make(const Dimension& dimension)
{
  return MakeRef<Framebuffer>(dimension);
}

Framebuffer::Framebuffer(const Dimension& dimension) :
    m_dimension(dimension), m_id(0), m_color_attachment(0), m_depth_attachment(0)
{
  Invalidate();
}

GE::Framebuffer::~Framebuffer()
{
  Clear();
}

void Framebuffer::Invalidate()
{
  if (!glIsTexture(u32(m_id)))
  {
    Clear();
  }

  // Create framebuffer
  {
    u32 fb_id = 0;
    glCreateFramebuffers(1, &fb_id);
    m_id = RendererID{ fb_id };
  }

  glBindFramebuffer(GL_FRAMEBUFFER, u32(m_id));

  // Create colors texture
  {
    u32 tex_id = 0;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex_id);
    m_color_attachment = RendererID{ tex_id };
  }
  glBindTexture(GL_TEXTURE_2D, u32(m_color_attachment));
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA8,
               i32(m_dimension.width),
               i32(m_dimension.height),
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, u32(m_color_attachment), 0);

  // Create depth texture
  {
    u32 tex_id = 0;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex_id);
    m_depth_attachment = RendererID{ tex_id };
  }
  glBindTexture(GL_TEXTURE_2D, u32(m_depth_attachment));
  glTexStorage2D(GL_TEXTURE_2D,
                 1,
                 GL_DEPTH24_STENCIL8,
                 i32(m_dimension.width),
                 i32(m_dimension.height));
  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         GL_DEPTH_STENCIL_ATTACHMENT,
                         GL_TEXTURE_2D,
                         u32(m_depth_attachment),
                         0);

  GE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
            "Framebuffer is incomplete")

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, u32(m_id));
  glViewport(0, 0, i32(m_dimension.width), i32(m_dimension.height));
}

void Framebuffer::Unbind() const
{
  GE_ASSERT(IsFramebufferBound(m_id), "Framebuffer not bound")
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RendererID GE::Framebuffer::GetColorAttachmentID() const
{
  return m_color_attachment;
}

const Dimension& GE::Framebuffer::GetDimension() const
{
  return m_dimension;
}

void GE::Framebuffer::Resize(Dimension dim)
{
  if (dim.IsEmpty())
    return;
  m_dimension = dim;
  Invalidate();
}

void Framebuffer::Clear()
{
  {
    const u32 i = u32(m_id);
    glDeleteFramebuffers(1, &i);
  }
  {
    const u32 i = u32(m_color_attachment);
    glDeleteTextures(1, &i);
  }
  {
    const u32 i = u32(m_depth_attachment);
    glDeleteTextures(1, &i);
  }
}
