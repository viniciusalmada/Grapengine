#ifndef GRAPHICENGINE3D_GE_APPLICATION_HPP
#define GRAPHICENGINE3D_GE_APPLICATION_HPP

class Application
{
public:
  Application(std::string&& title, unsigned int width, unsigned int height);
  virtual ~Application();

private:
  struct Impl;
  std::unique_ptr<Impl> m_pimpl;
};

#endif // GRAPHICENGINE3D_GE_APPLICATION_HPP
