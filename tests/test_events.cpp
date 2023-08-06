#include "ge_event.hpp"

#include <GLFW/glfw3.h>
#include <gtest/gtest.h>

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
  Event key_press_ev{ KeyPressData(EvType::KEY_PRESS, GLFW_KEY_A) };
  EXPECT_EQ(key_press_ev.GetType(), EvType::KEY_PRESS);
}

TEST(Event, KeyPressDataDispatcher)
{
  Event key_press_ev{ KeyPressData(EvType::KEY_PRESS, GLFW_KEY_A) };

  Event::Dispatch(EvType::KEY_PRESS,
                  key_press_ev,
                  [](const EvData& ev)
                  {
                    const auto& [type, key] = *std::get_if<KeyPressData>(&ev);
                    EXPECT_EQ(type, EvType::KEY_PRESS);

                    return key == GLFW_KEY_A;
                  });
  EXPECT_TRUE(key_press_ev.IsHandled());
}

TEST(Event, KeyReleaseData)
{
  Event key_rel_ev{ KeyPressData(EvType::KEY_RELEASE, GLFW_KEY_B) };
  EXPECT_EQ(key_rel_ev.GetType(), EvType::KEY_RELEASE);
}

TEST(Event, KeyReleaseDataDispatcher)
{
  Event key_rel_ev{ KeyPressData(EvType::KEY_RELEASE, GLFW_KEY_B) };

  Event::Dispatch(EvType::KEY_RELEASE,
                  key_rel_ev,
                  [](const EvData& ev)
                  {
                    const auto& [type, key] = *std::get_if<KeyReleaseData>(&ev);
                    EXPECT_EQ(type, EvType::KEY_RELEASE);

                    return key == GLFW_KEY_B;
                  });
  EXPECT_TRUE(key_rel_ev.IsHandled());
}

TEST(Event, MouseButtonPressData)
{
  Event mouse_press{ MouseButtonPressData(EvType::MOUSE_BUTTON_PRESSED, GLFW_MOUSE_BUTTON_1) };
  EXPECT_EQ(mouse_press.GetType(), EvType::MOUSE_BUTTON_PRESSED);
}

TEST(Event, MouseButtonPressDataDispatcher)
{
  Event mouse_press{ MouseButtonPressData(EvType::MOUSE_BUTTON_PRESSED, GLFW_MOUSE_BUTTON_1) };

  Event::Dispatch(EvType::MOUSE_BUTTON_PRESSED,
                  mouse_press,
                  [](const EvData& ev)
                  {
                    const auto& [type, key] = *std::get_if<MouseButtonPressData>(&ev);
                    EXPECT_EQ(type, EvType::MOUSE_BUTTON_PRESSED);

                    return key == GLFW_MOUSE_BUTTON_1;
                  });
  EXPECT_TRUE(mouse_press.IsHandled());
}

TEST(Event, MouseButtonReleaseData)
{
  Event mouse_rel{ MouseButtonReleaseData(EvType::MOUSE_BUTTON_RELEASE, GLFW_MOUSE_BUTTON_2) };
  EXPECT_EQ(mouse_rel.GetType(), EvType::MOUSE_BUTTON_RELEASE);
}

TEST(Event, MouseButtonRelDataDispatcher)
{
  Event mouse_rel{ MouseButtonReleaseData(EvType::MOUSE_BUTTON_RELEASE, GLFW_MOUSE_BUTTON_2) };

  Event::Dispatch(EvType::MOUSE_BUTTON_RELEASE,
                  mouse_rel,
                  [](const EvData& ev)
                  {
                    const auto& [type, key] = *std::get_if<MouseButtonReleaseData>(&ev);
                    EXPECT_EQ(type, EvType::MOUSE_BUTTON_RELEASE);

                    return key == GLFW_MOUSE_BUTTON_2;
                  });
  EXPECT_TRUE(mouse_rel.IsHandled());
}