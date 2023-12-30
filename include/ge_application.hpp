#ifndef GRAPHIC_ENGINE3D_GE_APPLICATION_HPP
#define GRAPHIC_ENGINE3D_GE_APPLICATION_HPP

class Application
{
public:
  GE3D Application(std::string&& title, unsigned int width, unsigned int height);
  GE3D virtual ~Application();

  GE3D void Run();

private:
  POINTER_TO_IMPLEMENTATION_IDIOM
};

#endif
