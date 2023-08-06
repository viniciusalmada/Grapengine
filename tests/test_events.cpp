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

  bool dispatch = Event::Dispatch(EvType::WINDOW_CLOSE,
                                  close_ev,
                                  [](const EvData& ev)
                                  {
                                    auto type = std::get<0>(*std::get_if<WindowCloseData>(&ev));
                                    EXPECT_EQ(type, EvType::WINDOW_CLOSE);
                                    return true;
                                  });
  EXPECT_TRUE(dispatch);
}

TEST(Event, KeyPressData)
{
  Event key_press_ev{ KeyPressData(EvType::KEY_PRESS, GLFW_KEY_A) };
  EXPECT_EQ(key_press_ev.GetType(), EvType::KEY_PRESS);
}

TEST(Event, KeyPressDataDispatcher)
{
  Event key_press_ev{ KeyPressData(EvType::KEY_PRESS, GLFW_KEY_A) };

  bool dispatch = Event::Dispatch(EvType::KEY_PRESS,
                                  key_press_ev,
                                  [](const EvData& ev)
                                  {
                                    const auto& [type, key] = *std::get_if<KeyPressData>(&ev);
                                    EXPECT_EQ(type, EvType::KEY_PRESS);

                                    return key == GLFW_KEY_A;
                                  });
  EXPECT_TRUE(dispatch);
}

TEST(Event, KeyReleaseData)
{
  Event key_rel_ev{ KeyPressData(EvType::KEY_RELEASE, GLFW_KEY_B) };
  EXPECT_EQ(key_rel_ev.GetType(), EvType::KEY_RELEASE);
}

TEST(Event, KeyReleaseDataDispatcher)
{
  Event key_rel_ev{ KeyPressData(EvType::KEY_RELEASE, GLFW_KEY_B) };

  bool dispatch = Event::Dispatch(EvType::KEY_RELEASE,
                                  key_rel_ev,
                                  [](const EvData& ev)
                                  {
                                    const auto& [type, key] = *std::get_if<KeyReleaseData>(&ev);
                                    EXPECT_EQ(type, EvType::KEY_RELEASE);

                                    return key == GLFW_KEY_B;
                                  });
  EXPECT_TRUE(dispatch);
}

TEST(Event, MouseButtonPressData)
{
  Event mouse_press{ MouseButtonPressData(EvType::MOUSE_BUTTON_PRESSED, GLFW_MOUSE_BUTTON_1) };
  EXPECT_EQ(mouse_press.GetType(), EvType::MOUSE_BUTTON_PRESSED);
}

TEST(Event, MouseButtonPressDataDispatcher)
{
  Event mouse_press{ MouseButtonPressData(EvType::MOUSE_BUTTON_PRESSED, GLFW_MOUSE_BUTTON_1) };

  bool dispatch = Event::Dispatch(EvType::MOUSE_BUTTON_PRESSED,
                                  mouse_press,
                                  [](const EvData& ev)
                                  {
                                    const auto& [type, key] =
                                      *std::get_if<MouseButtonPressData>(&ev);
                                    EXPECT_EQ(type, EvType::MOUSE_BUTTON_PRESSED);

                                    return key == GLFW_KEY_B;
                                  });
  EXPECT_TRUE(dispatch);
}