#include "renderer/ge_framebuffer.hpp"

#include <core/ge_assert.hpp>
#include <glad/glad.h>

using namespace GE;

namespace
{
  bool IsFramebufferBound(u32 fb)
  {
    i32 current_fb = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &current_fb);
    const bool is_any_fb_bound = current_fb != 0;
    if (!is_any_fb_bound)
      return false;

    const bool is_fb_bound = current_fb == i32(fb);
    if (!is_fb_bound)
      return false;

    return true;
  }

}

Ref<Framebuffer> Framebuffer::Make(const FBSpecs& specs)
{
  return MakeRef<Framebuffer>(specs);
}

Framebuffer::Framebuffer(const FBSpecs& specs)
{
  m_specs = specs;
  Invalidate();
}

GE::Framebuffer::~Framebuffer()
{
  Clear();
}

void Framebuffer::Invalidate()
{
  if (!glIsTexture(m_id))
  {
    Clear();
  }

  // Create framebuffer
  glCreateFramebuffers(1, &m_id);
  glBindFramebuffer(GL_FRAMEBUFFER, m_id);

  // Create colors texture
  glCreateTextures(GL_TEXTURE_2D, 1, &m_color_attachment);
  glBindTexture(GL_TEXTURE_2D, m_color_attachment);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA8,
               m_specs.width,
               m_specs.height,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_color_attachment, 0);

  // Create depth texture
  glCreateTextures(GL_TEXTURE_2D, 1, &m_depth_attachment);
  glBindTexture(GL_TEXTURE_2D, m_depth_attachment);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specs.width, m_specs.height);
  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         GL_DEPTH_STENCIL_ATTACHMENT,
                         GL_TEXTURE_2D,
                         m_depth_attachment,
                         0);

  GE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
            "Framebuffer is incomplete")

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_id);
  glViewport(0, 0, m_specs.width, m_specs.height);
}

void Framebuffer::Unbind()
{
  GE_ASSERT(IsFramebufferBound(m_id), "Framebuffer not bound")
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

u32 GE::Framebuffer::GetColorAttachmentID() const
{
  return m_color_attachment;
}

IVec2 GE::Framebuffer::GetSize() const
{
  return { m_specs.width, m_specs.height };
}

void GE::Framebuffer::Resize(i32 w, i32 h)
{
  if (w == 0 || h == 0)
    return;
  m_specs.width = w;
  m_specs.height = h;
  Invalidate();
}

const FBSpecs& GE::Framebuffer::GetSpec() const
{
  return m_specs;
}

void Framebuffer::Clear()
{

  glDeleteFramebuffers(1, &m_id);
  glDeleteTextures(1, &m_color_attachment);
  glDeleteTextures(1, &m_depth_attachment);
}
