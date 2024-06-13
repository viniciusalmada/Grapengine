#ifndef GRAPENGINE_CAMCONTROLLER_HPP
#define GRAPENGINE_CAMCONTROLLER_HPP

#include "grapengine.hpp"

using namespace GE;

class CamController final : public ScriptableEntity
{
public:
  CamController(Entity e, Scene& s);
  ~CamController() override;

  void OnCreate() override;
  void OnDestroy() override;
  void OnUpdate(TimeStep ts) override;
};

#endif // GRAPENGINE_CAMCONTROLLER_HPP
