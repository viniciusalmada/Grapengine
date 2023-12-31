#include "ge_application.hpp"
#include "ge_drawable.hpp"
#include "ge_window.hpp"

#include <ge_circle_shape.hpp>
#include <ge_rect_shape.hpp>
#include <iostream>
#include <chrono>

int main()
{
  u32 dim = 800;
  Application application{ "Graphic Engine", dim, dim };

  constexpr u32 side_circles = 10;
  float x = dim / (float)side_circles * 0.1f;
  float y = dim / (float)side_circles * 0.1f;
  float radius = (dim / (float)side_circles * 0.8f) / 2.0f;
  std::vector<Ref<CircleShape>> rects;
  rects.reserve(side_circles * side_circles);
  auto start = std::chrono::high_resolution_clock::now();
  for (u32 i = 0; i < side_circles; ++i)
  {
    for (u32 j = 0; j < side_circles; ++j)
    {
      auto c = MakeRef<CircleShape>(x + radius, y + radius, radius);
      rects.push_back(c);
      x += dim / (float)side_circles;
    }
    x = dim / (float)side_circles * 0.1f;
    y += dim / (float)side_circles;
    std::cout << i / (float)side_circles * 100.0f << "% completed" << std::endl;
  }
  std::cout << "Finish objects allocations" << std::endl;
  auto end = std::chrono::high_resolution_clock::now();
  auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Costed " << ms_int << std::endl;

  application.Run(
    [&](Window& window)
    {
      window.Clear();
      for (const auto& item : rects)
        window.Draw(item);
    });
  return 0;
}
