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
                                  [](Event& ev)
                                  {
                                    EXPECT_EQ(ev.GetType(), EvType::WINDOW_CLOSE);
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
                                  [](Event& ev)
                                  {
                                    EXPECT_EQ(ev.GetType(), EvType::KEY_PRESS);
                                    const KeyPressData& data =
                                      *std::get_if<KeyPressData>(&ev.GetData());
                                    int key = std::get<1>(data);

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
                                  [](Event& ev)
                                  {
                                    EXPECT_EQ(ev.GetType(), EvType::KEY_RELEASE);
                                    const KeyPressData& data =
                                      *std::get_if<KeyPressData>(&ev.GetData());
                                    int key = std::get<1>(data);

                                    return key == GLFW_KEY_B;
                                  });
  EXPECT_TRUE(dispatch);
}