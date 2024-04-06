#ifndef GRAPENGINE_GE_FRAMEBUFFER_HPP
#define GRAPENGINE_GE_FRAMEBUFFER_HPP

#include "math/ge_vector.hpp"

namespace GE
{
  struct FBSpecs
  {
    i32 width = 1, height = 1;
    u32 samples = 1;
    bool swap_chain_target = false;
  };

  class Framebuffer
  {
  public:
    static Ref<Framebuffer> Make(const FBSpecs& specs);

    explicit Framebuffer(const FBSpecs& specs);
    ~Framebuffer();

    void Invalidate();
    void Resize(i32 w, i32 h);

    void Bind();
    void Unbind();

    [[nodiscard]] u32 GetColorAttachmentID() const;

    [[nodiscard]] IVec2 GetSize() const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_GE_FRAMEBUFFER_HPP
