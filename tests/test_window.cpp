#include "ge_window.hpp"

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
  auto window = std::make_unique<Window>(WindowProps{});
  EXPECT_NE(window, nullptr);
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}