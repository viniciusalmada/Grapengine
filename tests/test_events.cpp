#include "ge_event.hpp"

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