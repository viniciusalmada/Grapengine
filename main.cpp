#include "ge_application.hpp"
#include "ge_drawable.hpp"
#include "ge_window.hpp"

#include <ge_rect_shape.hpp>
#include <iostream>

int main()
{
  Application application{ "Graphic Engine", 512, 512 };

  auto d = MakeRef<RectShape>(-0.5f, -0.5f, 0.4f, 0.2f);
  //  auto d2 = MakeRef<Drawable>(-0.5f, 0.5f, 0.4f);
  //  auto d3 = MakeRef<Drawable>(0.5f, -0.5f, 0.4f);
  //  auto d4 = MakeRef<Drawable>(0.5f, 0.5f, 0.4f);
  //  auto d2 = MakeRef<Drawable>(-0.25f, -0.25f, 0.5f, 0.5f);

  application.Run(
    [&](Window& window)
    {
      window.Clear();
      window.Draw(d);
//      window.Draw(d2);
//      window.Draw(d3);
//      window.Draw(d4);
      //      canvas->Draw(d2);
    });
  return 0;
}
