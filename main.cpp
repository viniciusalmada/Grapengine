#include "ge.hpp"

#include <chrono>
#include <drawables/ge_cube.hpp>
#include <drawables/ge_rect_shape.hpp>
#include <iostream>
#include <renderer/ge_shaders_library.hpp>

const Vec3 cubePositions[] = {
  Vec3(0.0f, 0.0f, 0.f),  //
  Vec3(0.0f, 1.0f, 0.f), //
  Vec3(1.0f, 2.0f, 0.f), //
  Vec3(2.0f, 3.0f, 0.f), //
  Vec3(3.0f, 4.0f, 0.f), //
  Vec3(4.0f, 5.0f, 0.f), //
  Vec3(5.0f, 6.0f, 0.f), //
  Vec3(6.0f, 7.0f, 0.f), //
  Vec3(7.0f, 8.0f, 0.f), //
  Vec3(8.0f, 9.0f, 0.f), //
  Vec3(9.0f, 10.0f, 0.f), //
  //  Vec3(2.0f, 5.0f, -5.f),   //
  //  Vec3(-1.5f, -2.2f, -1.f), //
  //  Vec3(-3.8f, -2.0f, -6.f), //
  //  Vec3(2.4f, -0.4f, -2.f),  //
  //  Vec3(-1.7f, 3.0f, -7.f),  //
  //  Vec3(1.3f, -2.0f, -3.f),  //
  //  Vec3(1.5f, 2.0f, -8.f),   //
  //  Vec3(1.5f, 0.2f, -4.f),   //
  //  Vec3(-1.3f, 1.0f, -9.f),  //
};

int main()
{
  u32 dim = 800;
  Application application{ "Graphic Engine", dim, dim };

  std::vector<Ref<CircleShape>> rects;
  {
    constexpr u32 side_circles = 1;
    float x = dim / (float)side_circles * 0.1f;
    float y = dim / (float)side_circles * 0.1f;
    float radius = (dim / (float)side_circles * 0.8f) / 2.0f;
    rects.reserve(side_circles * side_circles);
    auto start = std::chrono::high_resolution_clock::now();
    for (u32 i = 0; i < side_circles; ++i)
    {
      for (u32 j = 0; j < side_circles; ++j)
      {
        u8 red = static_cast<u8>(x / dim * 255);
        u8 blue = static_cast<u8>(y / dim * 255);
        auto c = MakeRef<CircleShape>(x + radius,
                                      y + radius,
                                      radius,
                                      Color{
                                        red,
                                        static_cast<u8>(Random::GenInt(0x00, 0xFF)),
                                        blue,
                                      },
                                      Shaders::POSITION_AND_COLOR);
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
  }

  //  Ref<RectShape> rect_shape =
  //    MakeRef<RectShape>(Vec3{ -5.0f, 0.0f, +5.0f },
  //                       Vec3{ +5.0f, 0.0f, +5.0f },
  //                       Vec3{ +5.0f, 0.0f, -5.0f },
  //                       Vec3{ -5.0f, 0.0f, -5.0f },
  //                       Colors::BLUE,
  //                       ShadersLibrary::Get().GetShader(Shaders::POSITION_AND_COLOR));
  //
  std::vector<Ref<Cube>> cubes;
  for (auto cubePosition : cubePositions)
  {
    cubes.emplace_back(MakeRef<Cube>(cubePosition.x,
                                     cubePosition.y,
                                     cubePosition.z,
                                     Shaders::POSITION_AND_TEXTURE2D));
  }

  application.Run(
    [&](Window& window)
    {
      window.Clear(Colors::WHITE);

      for (const auto& cube : cubes)
        window.Draw(cube);
    });
  return 0;
}
