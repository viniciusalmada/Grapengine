#ifndef GRAPHICENGINE3D_GE_ISHADER_PROGRAM_HPP
#define GRAPHICENGINE3D_GE_ISHADER_PROGRAM_HPP

class IShaderProgram
{
public:
  virtual void Activate() = 0;
  virtual void Deactivate() = 0;
};

#endif // GRAPHICENGINE3D_GE_ISHADER_HPP
