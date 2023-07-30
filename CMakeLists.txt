cmake_minimum_required(VERSION 3.0)
project(GraphicEngine3D)

set(CMAKE_CXX_STANDARD 20)

# #############################################################################
# GLFW library
add_subdirectory(vendor/glfw)

# #############################################################################
# GLAD library
add_subdirectory(vendor/GLAD)

# #############################################################################
# Engine
add_executable(GraphicEngine3D
    src/main.cpp
    src/ge_application.cpp
    src/ge_window.cpp
    src/ge_renderer.cpp
    src/ge_vector.cpp
    src/ge_entities.cpp
    src/ge_shader.cpp
    src/ge_event.cpp
)
target_precompile_headers(GraphicEngine3D PRIVATE include/ge_pch.hpp)
target_include_directories(GraphicEngine3D PRIVATE include)
target_include_directories(GraphicEngine3D SYSTEM PUBLIC
    vendor/GLFW/include
    vendor/GLAD/include)
target_compile_definitions(GraphicEngine3D PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(GraphicEngine3D PRIVATE /WX /W4)

target_link_libraries(GraphicEngine3D
    PUBLIC GLAD
    PUBLIC glfw)
if(WIN32)
  target_link_libraries(GraphicEngine3D PRIVATE opengl32.lib)
elseif(UNIX)
  target_link_libraries(GraphicEngine3D PRIVATE GL)
endif(WIN32)

# #############################################################################
# Tests
add_subdirectory(tests)