#ifndef GRAPHIC_ENGINE3D_GE_APPLICATION_HPP
#define GRAPHIC_ENGINE3D_GE_APPLICATION_HPP

#include "ge_system.hpp"

class Window;

class Application
{
public:
  GE3D Application(std::string&& title, u32 width, u32 height);
  GE3D virtual ~Application();

  GE3D void Run(const std::function<void(Window&)>& onLoop);

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif
