#ifndef GRAPENGINE_ISHADER_PROGRAM_HPP
#define GRAPENGINE_ISHADER_PROGRAM_HPP
namespace GE
{
  class IShaderProgram
  {
  public:
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
  };
}

#endif // GRAPENGINE_ISHADER_HPP
