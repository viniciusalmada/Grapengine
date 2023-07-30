cmake_minimum_required(VERSION 3.0)
project(GraphicEngine3D)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENGINE_NAME GraphicEngine3D)

# #############################################################################
# GLFW library
add_subdirectory(vendor/glfw)

# #############################################################################
# GLAD library
add_subdirectory(vendor/GLAD)

# #############################################################################
# Engine
add_subdirectory(src)

# #############################################################################
# App
add_executable(App main.cpp)
target_link_libraries(App PRIVATE ${ENGINE_NAME})
target_precompile_headers(App PRIVATE include/ge_pch.hpp)
target_compile_options(App PRIVATE /WX /W4)

# #############################################################################
# Tests
add_subdirectory(tests)