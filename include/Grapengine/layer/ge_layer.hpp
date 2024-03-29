#ifndef GE_LAYER_HPP
#define GE_LAYER_HPP

namespace GE
{
  class Event;
  class TimeStep;

  class Layer
  {
  public:
    GE3D explicit Layer(std::string_view name);

    GE3D virtual ~Layer();

    GE3D virtual void OnAttach();

    GE3D virtual void OnDetach();

    virtual void OnUpdate(TimeStep);

    virtual void OnImGuiUpdate();

    GE3D virtual void OnEvent(Event&);

    [[nodiscard]] const std::string& GetName() const;

  protected:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GE_LAYER_HPP
