#ifndef GRAPENGINE_GE_FRAMEBUFFER_HPP
#define GRAPENGINE_GE_FRAMEBUFFER_HPP

#include "math/ge_vector.hpp"
#include "utils/ge_dimension.hpp"

namespace GE
{
  struct FBSpecs
  {
    Dimension dimension;
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
    void Resize(Dimension dim);

    void Bind();
    void Unbind();

    [[nodiscard]] const FBSpecs& GetSpec() const;

    [[nodiscard]] u32 GetColorAttachmentID() const;

    [[nodiscard]] const Dimension& GetDimension() const;

  private:
    void Clear();

    FBSpecs m_specs;
    u32 m_id = 0;
    u32 m_color_attachment = 0;
    u32 m_depth_attachment = 0;
  };
}

#endif // GRAPENGINE_GE_FRAMEBUFFER_HPP
