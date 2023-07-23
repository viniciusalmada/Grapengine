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

# #############################################################################
# Engine
add_executable(${PROJECT} main.cpp ge_application.cpp ge_application.hpp ge_window.cpp ge_window.hpp ge_renderer.cpp ge_renderer.hpp ge_vector.cpp ge_vector.hpp ge_entities.hpp ge_entities.cpp)
target_precompile_headers(${PROJECT} PRIVATE ge_pch.hpp)
target_include_directories(${PROJECT} SYSTEM PUBLIC
    vendor/GLFW/include
    vendor/GLAD/include)
target_compile_definitions(${PROJECT} PRIVATE GLFW_INCLUDE_NONE)

target_link_libraries(${PROJECT}
    PUBLIC GLAD
    PUBLIC glfw)
if(WIN32)
  target_link_libraries(${PROJECT} PRIVATE opengl32.lib)
elseif(UNIX)
  target_link_libraries(${PROJECT} PRIVATE GL)
endif(WIN32)