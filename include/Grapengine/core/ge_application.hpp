#ifndef GRAPENGINE_APPLICATION_HPP
#define GRAPENGINE_APPLICATION_HPP

class Window;

class Application
{
public:
  GE3D Application(std::string&& title, u32 width, u32 height);
  GE3D virtual ~Application();

  GE3D void Run(const std::function<void(Window&)>& onLoop) const;

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif