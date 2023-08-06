#include "ge_window.hpp"

#include <gtest/gtest.h>

TEST(Window, Initialization)
{
  auto window = std::make_unique<Window>(WindowProps{ "Test", 100, 200 }, nullptr);
  EXPECT_NE(window, nullptr);

  EXPECT_EQ(window->GetWidth(), 100);

  EXPECT_EQ(window->GetHeight(), 200);
}
