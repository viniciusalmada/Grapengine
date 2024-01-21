#include "Grapengine/grapengine.hpp"
#include "core/ge_entry_point.hpp"

class Client : public GE::Application
{
public:
  Client() : Application("Grapengine", 1280, 720, "assets/ic_grapengine.png") {}
};

GE::Scope<GE::Application> CreateApplication()
{
  return GE::MakeScope<Client>();
}