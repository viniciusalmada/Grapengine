#ifndef GRAPHICENGINE3D_GE_WINDOW_HPP
#define GRAPHICENGINE3D_GE_WINDOW_HPP

struct WindowProps
{
  std::string title;
  unsigned int width;
  unsigned int height;

  explicit WindowProps(std::string title = "Graphic Engine",
                       unsigned int w = 1280,
                       unsigned int h = 720) :
      title(std::move(title)),
      width(w),
      height(h)
  {
  }
};

class Window
{
public:
  explicit Window(const WindowProps& props);
  ~Window();

  [[nodiscard]] unsigned int GetWidth() const;
  [[nodiscard]] unsigned int GetHeight() const;

  //  void SetEventCallback(const EventCallbackFn& callback) ;

  void SetVsync(bool enabled);
//  bool IsVsync() const;

//  std::any GetNativeWindow() const;

  void OnUpdate();

private:
  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif // GRAPHICENGINE3D_GE_WINDOW_HPP
