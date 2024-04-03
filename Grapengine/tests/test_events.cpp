#include "events/ge_event.hpp"

#include <GLFW/glfw3.h>
#include <gtest/gtest.h>

using namespace GE;

TEST(Event, WindowCloseData)
{
  Event close_ev{ std::make_tuple(EvType::WINDOW_CLOSE) };
  EXPECT_EQ(close_ev.GetType(), EvType::WINDOW_CLOSE);
}

TEST(Event, WindowCloseDataDispatcher)
{
  Event close_ev{ std::make_tuple(EvType::WINDOW_CLOSE) };

  Event::Dispatch(EvType::WINDOW_CLOSE,
                  close_ev,
                  [](const EvData& ev)
                  {
                    auto type = std::get<0>(*std::get_if<WindowCloseData>(&ev));
                    EXPECT_EQ(type, EvType::WINDOW_CLOSE);
                    return true;
                  });
  EXPECT_TRUE(close_ev.IsHandled());
}

TEST(Event, KeyPressData)
{
  Event key_press_ev{ KeyPressData(EvType::KEY_PRESS, KeyCode::K_A) };
  EXPECT_EQ(key_press_ev.GetType(), EvType::KEY_PRESS);
}

TEST(Event, KeyPressDataDispatcher)
{
  Event key_press_ev{ KeyPressData(EvType::KEY_PRESS, KeyCode::K_A) };

  Event::Dispatch(EvType::KEY_PRESS,
                  key_press_ev,
                  [](const EvData& ev)
                  {
                    const auto& [type, key] = *std::get_if<KeyPressData>(&ev);
                    EXPECT_EQ(type, EvType::KEY_PRESS);

                    return key == KeyCode::K_A;
                  });
  EXPECT_TRUE(key_press_ev.IsHandled());
}

TEST(Event, KeyReleaseData)
{
  Event key_rel_ev{ KeyPressData(EvType::KEY_RELEASE, KeyCode::K_B) };
  EXPECT_EQ(key_rel_ev.GetType(), EvType::KEY_RELEASE);
}

TEST(Event, KeyReleaseDataDispatcher)
{
  Event key_rel_ev{ KeyPressData(EvType::KEY_RELEASE, KeyCode::K_B) };

  Event::Dispatch(EvType::KEY_RELEASE,
                  key_rel_ev,
                  [](const EvData& ev)
                  {
                    const auto& [type, key] = *std::get_if<KeyReleaseData>(&ev);
                    EXPECT_EQ(type, EvType::KEY_RELEASE);

                    return key == KeyCode::K_B;
                  });
  EXPECT_TRUE(key_rel_ev.IsHandled());
}

TEST(Event, MouseButtonPressData)
{
  Event mouse_press{ MouseButtonPressData(EvType::MOUSE_BUTTON_PRESSED, KeyCode::MOUSE_BT_LEFT) };
  EXPECT_EQ(mouse_press.GetType(), EvType::MOUSE_BUTTON_PRESSED);
}

TEST(Event, MouseButtonPressDataDispatcher)
{
  Event mouse_press{ MouseButtonPressData(EvType::MOUSE_BUTTON_PRESSED, KeyCode::MOUSE_BT_LEFT) };

  Event::Dispatch(EvType::MOUSE_BUTTON_PRESSED,
                  mouse_press,
                  [](const EvData& ev)
                  {
                    const auto& [type, key] = *std::get_if<MouseButtonPressData>(&ev);
                    EXPECT_EQ(type, EvType::MOUSE_BUTTON_PRESSED);

                    return key == KeyCode::MOUSE_BT_LEFT;
                  });
  EXPECT_TRUE(mouse_press.IsHandled());
}

TEST(Event, MouseButtonReleaseData)
{
  Event mouse_rel{ MouseButtonReleaseData(EvType::MOUSE_BUTTON_RELEASE, KeyCode::MOUSE_BT_RIGHT) };
  EXPECT_EQ(mouse_rel.GetType(), EvType::MOUSE_BUTTON_RELEASE);
}

TEST(Event, MouseButtonRelDataDispatcher)
{
  Event mouse_rel{ MouseButtonReleaseData(EvType::MOUSE_BUTTON_RELEASE, KeyCode::MOUSE_BT_RIGHT) };

  Event::Dispatch(EvType::MOUSE_BUTTON_RELEASE,
                  mouse_rel,
                  [](const EvData& ev)
                  {
                    const auto& [type, key] = *std::get_if<MouseButtonReleaseData>(&ev);
                    EXPECT_EQ(type, EvType::MOUSE_BUTTON_RELEASE);

                    return key == KeyCode::MOUSE_BT_RIGHT;
                  });
  EXPECT_TRUE(mouse_rel.IsHandled());
}

TEST(Event, MouseMoveData)
{
  Event mouse_move{ MouseMoveData(EvType::MOUSE_MOVE, 1.0f, 2.0f) };
  EXPECT_EQ(mouse_move.GetType(), EvType::MOUSE_MOVE);
}

TEST(Event, MouseMoveDataDispatcher)
{
  Event mouse_move{ MouseMoveData(EvType::MOUSE_MOVE, 1.0f, 2.0f) };

  Event::Dispatch(EvType::MOUSE_MOVE,
                  mouse_move,
                  [](const EvData& ev)
                  {
                    const auto& [type, x, y] = *std::get_if<MouseMoveData>(&ev);
                    EXPECT_EQ(type, EvType::MOUSE_MOVE);

                    return x > 0.0f && y > 0.0f;
                  });
  EXPECT_TRUE(mouse_move.IsHandled());
}

TEST(Event, MouseScrollData)
{
  Event mouse_scroll{ MouseScrollData(EvType::MOUSE_SCROLL, 0.5f, -0.5f) };
  EXPECT_EQ(mouse_scroll.GetType(), EvType::MOUSE_SCROLL);
}

TEST(Event, MouseScrollDataDispatcher)
{
  Event mouse_scroll{ MouseScrollData(EvType::MOUSE_SCROLL, 0.5f, -0.5f) };

  Event::Dispatch(EvType::MOUSE_SCROLL,
                  mouse_scroll,
                  [](const EvData& ev)
                  {
                    const auto& [type, x, y] = *std::get_if<MouseMoveData>(&ev);
                    EXPECT_EQ(type, EvType::MOUSE_SCROLL);

                    return x > 0.0f && y < 0.0f;
                  });
  EXPECT_TRUE(mouse_scroll.IsHandled());
}