cmake_minimum_required(VERSION 3.0)
project(GraphicEngine3D)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT GraphicEngine3D)

add_executable(${PROJECT} main.cpp ge_application.cpp ge_application.hpp ge_window.cpp ge_window.hpp)
target_precompile_headers(${PROJECT} PRIVATE ge_pch.hpp)
