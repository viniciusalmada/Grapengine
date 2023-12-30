#ifndef GRAPHIC_ENGINE3D_GE_APPLICATION_HPP
#define GRAPHIC_ENGINE3D_GE_APPLICATION_HPP

class Window;

class Application
{
public:
  GE3D Application(std::string&& title, u32 width, u32 height);
  GE3D virtual ~Application();

  GE3D void Run();

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif
