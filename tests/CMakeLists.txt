enable_testing()

add_executable(EngineTests
  test_main.cpp
  test_window.cpp
  test_events.cpp
  test_vector.cpp
  test_transformations.cpp
  test_shader.cpp
  test_vertex_array.cpp
  test_random.cpp
  test_camera.cpp
)
find_package(GTest CONFIG REQUIRED)
target_link_libraries(EngineTests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

target_include_directories(EngineTests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_precompile_headers(EngineTests PRIVATE ${CMAKE_SOURCE_DIR}/include/ge_pch.hpp)
target_link_libraries(EngineTests
  PRIVATE ${ENGINE_NAME}
)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(EngineTests PRIVATE glfw)