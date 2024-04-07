#include "renderer/ge_framebuffer.hpp"

#include <core/ge_assert.hpp>
#include <glad/glad.h>

using namespace GE;

namespace
{
  bool IsFramebufferBound(u32 fb)
  {
    u32 current_fb = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (i32*)(&current_fb));
    const bool is_any_fb_bound = current_fb != 0;
    if (!is_any_fb_bound)
      return false;

    const bool is_fb_bound = current_fb == fb;
    if (!is_fb_bound)
      return false;

    return true;
  }

}

struct Framebuffer::Impl
{
  FBSpecs specs;
  u32 id = 0;
  u32 color_attachment = 0;
  u32 depth_attachment = 0;

  void Clear()
  {
    glDeleteFramebuffers(1, &id);
    glDeleteTextures(1, &color_attachment);
    glDeleteTextures(1, &depth_attachment);
  }
};

Ref<Framebuffer> Framebuffer::Make(const FBSpecs& specs)
{
  return MakeRef<Framebuffer>(specs);
}

Framebuffer::Framebuffer(const FBSpecs& specs) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->specs = specs;
  Invalidate();
}

GE::Framebuffer::~Framebuffer()
{
  m_pimpl->Clear();
}

void Framebuffer::Invalidate()
{
  if (!glIsTexture(m_pimpl->id))
  {
    m_pimpl->Clear();
  }

  // Create framebuffer
  glCreateFramebuffers(1, &m_pimpl->id);
  glBindFramebuffer(GL_FRAMEBUFFER, m_pimpl->id);

  // Create colors texture
  glCreateTextures(GL_TEXTURE_2D, 1, &m_pimpl->color_attachment);
  glBindTexture(GL_TEXTURE_2D, m_pimpl->color_attachment);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA8,
               m_pimpl->specs.width,
               m_pimpl->specs.height,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_pimpl->color_attachment, 0);

  // Create depth texture
  glCreateTextures(GL_TEXTURE_2D, 1, &m_pimpl->depth_attachment);
  glBindTexture(GL_TEXTURE_2D, m_pimpl->depth_attachment);
  glTexStorage2D(GL_TEXTURE_2D,
                 1,
                 GL_DEPTH24_STENCIL8,
                 m_pimpl->specs.width,
                 m_pimpl->specs.height);
  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         GL_DEPTH_STENCIL_ATTACHMENT,
                         GL_TEXTURE_2D,
                         m_pimpl->depth_attachment,
                         0);

  GE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
            "Framebuffer is incomplete")

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_pimpl->id);
  glViewport(0, 0, m_pimpl->specs.width, m_pimpl->specs.height);
}

void Framebuffer::Unbind()
{
  GE_ASSERT(IsFramebufferBound(m_pimpl->id), "Framebuffer not bound")
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

u32 GE::Framebuffer::GetColorAttachmentID() const
{
  return m_pimpl->color_attachment;
}

IVec2 GE::Framebuffer::GetSize() const
{
  return { m_pimpl->specs.width, m_pimpl->specs.height };
}

void GE::Framebuffer::Resize(i32 w, i32 h)
{
  if (w == 0 || h == 0)
    return;
  m_pimpl->specs.width = w;
  m_pimpl->specs.height = h;
  Invalidate();
}

const FBSpecs& GE::Framebuffer::GetSpec() const
{
  return m_pimpl->specs;
}
