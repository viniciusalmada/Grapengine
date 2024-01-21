#ifndef GE_LAYER_HPP
#define GE_LAYER_HPP

namespace GE
{
  class Event;
  class TimeStep;

  class Layer
  {
  public:
    explicit Layer(const std::string& name);

    virtual ~Layer();

    virtual void OnAttach();

    virtual void OnDetach();

    virtual void OnUpdate(TimeStep);

    virtual void OnEvent(Event&);

    [[nodiscard]] const std::string& GetName() const;

  protected:
    POINTER_TO_IMPLEMENTATION_IDIOM
  };
}

#endif // GE_LAYER_HPP
