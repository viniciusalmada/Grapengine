#ifndef GRAPHICENGINE3D_GE_APPLICATION_HPP
#define GRAPHICENGINE3D_GE_APPLICATION_HPP

class Application
{
public:
  GE3D Application(std::string&& title, unsigned int width, unsigned int height);
  GE3D virtual ~Application();

  GE3D void Run();

private:
  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif // GRAPHICENGINE3D_GE_APPLICATION_HPP
