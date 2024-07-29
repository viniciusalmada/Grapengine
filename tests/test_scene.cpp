#include "grapengine.hpp"

#include <gtest/gtest.h>

#if defined(GE_CLANG_COMPILER)
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif

TEST(Scene, CreateEntities)
{
  GE::Ptr<GE::Scene> scene = GE::Scene::Make("TestScene");
  GE::Entity first_ent = scene->CreateEntity("First");
  GE::Entity second_ent = scene->CreateEntity("Second");
  GE::Entity third_ent = scene->CreateEntity("Third");

  ASSERT_TRUE(first_ent);
  ASSERT_TRUE(second_ent);
  ASSERT_TRUE(third_ent);

  ASSERT_NE(i32(first_ent), i32(second_ent));
  ASSERT_NE(i32(second_ent), i32(third_ent));
  ASSERT_NE(i32(first_ent), i32(third_ent));
}

TEST(Scene, AddComponents)
{
  GE::Ptr<GE::Scene> scene = GE::Scene::Make("TestScene");
  GE::Entity first_ent = scene->CreateEntity("First");
  GE::Entity second_ent = scene->CreateEntity("Second");
  [[maybe_unused]] GE::Entity third_ent = scene->CreateEntity("Third");

  ASSERT_DEATH(scene->AddComponent<GE::TagComponent>(first_ent, "Other"), "");
  auto& transf = scene->AddComponent<GE::TransformComponent>(second_ent);
  transf.Position() = GE::Vec3{};

  ASSERT_EQ(scene->GetComponent<GE::TransformComponent>(second_ent).Position().x, GE::Vec3{}.x);
}
