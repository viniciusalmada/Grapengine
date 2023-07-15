cmake_minimum_required(VERSION 3.0)
project(GraphicEngine3D)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT GraphicEngine3D)

# #############################################################################
# GLFW library
add_subdirectory(vendor/glfw)

# #############################################################################
# GLAD library
add_subdirectory(vendor/GLAD)

add_executable(${PROJECT} main.cpp ge_application.cpp ge_application.hpp ge_window.cpp ge_window.hpp)
target_precompile_headers(${PROJECT} PRIVATE ge_pch.hpp)
