#ifndef GRAPENGINE_GE_FRAMEBUFFER_HPP
#define GRAPENGINE_GE_FRAMEBUFFER_HPP

namespace GE
{
  struct FBSpecs
  {
    i32 width, height;
    u32 samples = 1;
    bool swap_chain_target = false;
  };

  class Framebuffer
  {
  public:
    static Ref<Framebuffer> Make(const FBSpecs& specs);

    explicit Framebuffer(const FBSpecs& specs);
    ~Framebuffer();

    void Invalidated();

    void Bind();
    void Unbind();

    [[nodiscard]] u32 GetColorAttachmentID() const;

  private:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GRAPENGINE_GE_FRAMEBUFFER_HPP
