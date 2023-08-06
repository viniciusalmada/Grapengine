#ifndef GRAPHIC_ENGINE3D_GE_WINDOW_HPP
#define GRAPHIC_ENGINE3D_GE_WINDOW_HPP

#include "ge_event.hpp"

struct WindowProps
{
  std::string title;
  unsigned int width;
  unsigned int height;

  explicit WindowProps(std::string title = "Graphic Engine",
                       unsigned int w = 1280,
                       unsigned int h = 720) :
      title(std::move(title)), width(w), height(h)
  {
  }
};

using EventCallbackFn = std::function<void(Event&)>;

class Window
{
public:
  GE3D explicit Window(const WindowProps& props, const EventCallbackFn& cb);
  GE3D ~Window();

  [[nodiscard]] GE3D unsigned int GetWidth() const;
  [[nodiscard]] GE3D unsigned int GetHeight() const;

  void SetVsync(bool enabled);

  void OnUpdate();

private:
  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif
