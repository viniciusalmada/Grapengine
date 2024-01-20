#include "ge.hpp"

#include <chrono>
#include <drawables/ge_cube.hpp>
#include <drawables/ge_cylinder.hpp>
#include <drawables/ge_rect_shape.hpp>
#include <iostream>
#include <renderer/ge_shaders_library.hpp>

const Vec3 cubePositions[] = {
  Vec3(0.0f, 0.0f, 0.f),  //
  Vec3(0.0f, 1.0f, 0.f),  //
  Vec3(1.0f, 2.0f, 0.f),  //
  Vec3(2.0f, 3.0f, 0.f),  //
  Vec3(3.0f, 4.0f, 0.f),  //
  Vec3(4.0f, 5.0f, 0.f),  //
  Vec3(5.0f, 6.0f, 0.f),  //
  Vec3(6.0f, 7.0f, 0.f),  //
  Vec3(7.0f, 8.0f, 0.f),  //
  Vec3(8.0f, 9.0f, 0.f),  //
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

  constexpr u32 width = 1280;
  constexpr u32 height = 720;
  Application application{ "Graphic Engine", width, height };

  //  Ref<RectShape> rect_shape =
  //    MakeRef<RectShape>(Vec3{ -5.0f, 0.0f, +5.0f },
  //                       Vec3{ +5.0f, 0.0f, +5.0f },
  //                       Vec3{ +5.0f, 0.0f, -5.0f },
  //                       Vec3{ -5.0f, 0.0f, -5.0f },
  //                       Colors::BLUE,
  //                       ShadersLibrary::Get().GetShader(Shaders::POSITION_AND_COLOR));
  //
  std::vector<Ref<Cube>> cubes;
  for (const auto [x, y, z] : cubePositions)
  {
    cubes.emplace_back(MakeRef<Cube>(x, y, z, Shaders::POSITION_AND_TEXTURE2D));
  }

  const auto axis_x = MakeRef<Cylinder>(Shaders::POSITION_AND_TEXTURE2D,
                                        .1f,
                                        Vec3{ 0, 0, 0 },
                                        Vec3{ 1, 0, 0 },
                                        1000.0f,
                                        Colors::RED);
  const auto axis_y = MakeRef<Cylinder>(Shaders::POSITION_AND_TEXTURE2D,
                                        .1f,
                                        Vec3{ 0, 0, 0 },
                                        Vec3{ 0, 1, 0 },
                                        1000.0f,
                                        Colors::BLUE);
  const auto axis_z = MakeRef<Cylinder>(Shaders::POSITION_AND_TEXTURE2D,
                                        .1f,
                                        Vec3{ 0, 0, 0 },
                                        Vec3{ 0, 0, 1 },
                                        1000.0f,
                                        Colors::GREEN);
  const auto plane_xz = MakeRef<RectShape>(
    Vec3{ -0, 0, -0 },
    Vec3{ 1000, 0, -0 },
    Vec3{ 1000, 0, 1000 },
    Vec3{ -0, 0, 1000 },
    Color{ 0x11, 0x11, 0xFF, 0x55 },
    Shaders::POSITION_AND_TEXTURE2D,
    std::string{
      R"(C:\Users\vinic\OneDrive\Imagens\325970914_595202895767349_4190762160840629530_n.jpg)" });

  const auto bar_bot = MakeRef<Cylinder>(Shaders::POSITION_AND_TEXTURE2D,
                                         .1f,
                                         Vec3{ 1, 1, 1 },
                                         Vec3{ 1, 0, 0 },
                                         2.0f,
                                         Colors::MAGENTA);
  const auto bar_left = MakeRef<Cylinder>(Shaders::POSITION_AND_TEXTURE2D,
                                          .1f,
                                          Vec3{ 3, 1, 1 },
                                          Vec3{ 0, 1, 0 },
                                          2.0f,
                                          Colors::MAGENTA);
  const auto bar_top = MakeRef<Cylinder>(Shaders::POSITION_AND_TEXTURE2D,
                                         .1f,
                                         Vec3{ 3, 3, 1 },
                                         Vec3{ -1, 0, 0 },
                                         2.0f,
                                         Colors::MAGENTA);
  const auto bar_right = MakeRef<Cylinder>(Shaders::POSITION_AND_TEXTURE2D,
                                           .1f,
                                           Vec3{ 1, 3, 1 },
                                           Vec3{ 0, -1, 0 },
                                           2.0f,
                                           Colors::MAGENTA);
  const auto frame = MakeRef<RectShape>( //
    Vec3{ 1, 1, 1 },
    Vec3{ 3, 1, 1 },
    Vec3{ 3, 3, 1 },
    Vec3{ 1, 3, 1 },
    Color{ 0x11, 0x11, 0xFF, 0x55 },
    Shaders::POSITION_AND_TEXTURE2D,
    std::string{
      R"(assets/wall.jpg)" });

  const auto frame2 = MakeRef<RectShape>(
    Vec3{ 3, 1, 10 },
    Vec3{ 1, 1, 10 },
    Vec3{ 1, 3, 10 },
    Vec3{ 3, 3, 10 },
    Color{ 0x11, 0x11, 0xFF, 0x55 },
    Shaders::POSITION_AND_TEXTURE2D,
    std::string{
      R"(assets/wall.jpg)" });

  application.Run(
    [&](const Window& window)
    {
      window.Clear(Colors::WHITE);

      // for (const auto& cube : cubes)
      // window.Draw(cube);

      window.Draw(axis_x);
      window.Draw(axis_y);
      window.Draw(axis_z);
      window.Draw(plane_xz);

      window.Draw(bar_bot);
      window.Draw(bar_left);
      window.Draw(bar_top);
      window.Draw(bar_right);
      window.Draw(frame);
      window.Draw(frame2);
    });
  return 0;
}
