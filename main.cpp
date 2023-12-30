#include "ge_application.hpp"
#include "ge_drawable.hpp"
#include "ge_window.hpp"

#include <ge_circle_shape.hpp>
#include <ge_rect_shape.hpp>
#include <iostream>

int main()
{
  Application application{ "Graphic Engine", 512, 512 };

  auto d = MakeRef<RectShape>(-0.5f, -0.5f, 0.4f, 0.2f);
  auto c = MakeRef<CircleShape>(+0.5f, +0.5f, 0.4f);

  float vel = 0.0025f;

  application.Run(
    [&](Window& window)
    {
      d->SetPosition(d->GetPosition().x + vel, d->GetPosition().y + vel);
      d->SetPosition(d->GetPosition().x + vel, d->GetPosition().y + vel);

      window.Clear();
      window.Draw(d);
      window.Draw(c);
    });
  return 0;
}
