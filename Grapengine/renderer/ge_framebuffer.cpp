#include "renderer/ge_framebuffer.hpp"

#include <core/ge_assert.hpp>
#include <glad/glad.h>

using namespace GE;

struct Framebuffer::Impl
{
  FBSpecs specs;
  u32 id = 0;
  u32 color_attachment;
  u32 depth_attachment;
};

Ref<Framebuffer> Framebuffer::Make(const FBSpecs& specs)
{
  return MakeRef<Framebuffer>(specs);
}

Framebuffer::Framebuffer(const FBSpecs& specs) : m_pimpl(MakeScope<Impl>())
{
  m_pimpl->specs = specs;
  Invalidated();
}

GE::Framebuffer::~Framebuffer()
{
  glDeleteFramebuffers(1, &m_pimpl->id);
}

void Framebuffer::Invalidated()
{
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
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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
            "Framebuffer is incomplete");

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_pimpl->id);
}

void Framebuffer::Unbind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

u32 GE::Framebuffer::GetColorAttachmentID() const
{
  return m_pimpl->color_attachment;
}
