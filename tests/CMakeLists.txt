enable_testing()

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif ()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
if (WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif (WIN32)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(EngineTests test_main.cpp test_window.cpp test_events.cpp test_vector.cpp test_transformations.cpp
  test_transformations.cpp)
target_include_directories(EngineTests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(EngineTests SYSTEM PUBLIC
  ${CMAKE_SOURCE_DIR}/vendor/glfw/include
)
target_precompile_headers(EngineTests PRIVATE ${CMAKE_SOURCE_DIR}/include/ge_pch.hpp)
target_link_libraries(EngineTests
  PRIVATE GTest::GTest
  PRIVATE ${ENGINE_NAME}
)