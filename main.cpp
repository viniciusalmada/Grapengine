#include "ge_application.hpp"
#include "ge_drawable.hpp"
#include "ge_window.hpp"

#include <iostream>

int main()
{
  Application application{ "Graphic Engine", 512, 512 };

  auto d = std::make_shared<Drawable>(-0.5f, -0.5f, 0.4f);
  auto d2 = std::make_shared<Drawable>(-0.5f, 0.5f, 0.4f);
  auto d3 = std::make_shared<Drawable>(0.5f, -0.5f, 0.4f);
  auto d4 = std::make_shared<Drawable>(0.5f, 0.5f, 0.4f);
  //  auto d2 = std::make_shared<Drawable>(-0.25f, -0.25f, 0.5f, 0.5f);

  application.Run(
    [&](Window& window)
    {
      window.Clear(Vec4{ 1.0f, 0.0f, 1.0f, 1.0f });
      window.Draw(d);
      window.Draw(d2);
      window.Draw(d3);
      window.Draw(d4);
      //      canvas->Draw(d2);
    });
  return 0;
}
