# #############################################################################
# Engine
add_library(${ENGINE_NAME} SHARED
  ge_application.cpp
  ge_event.cpp
  ge_gl_checkers.cpp
  ge_index_buffer.cpp
  ge_io.cpp
  ge_renderer.cpp
  ge_shader.cpp
  ge_shaders_library.cpp
  ge_texture_2d.cpp
  ge_transformations.cpp
  ge_vector.cpp
  ge_vertex_array.cpp
  ge_vertex_buffer.cpp
  ge_window.cpp
  ge_canvas.cpp
  ge_assert.cpp
  ge_rect_shape.cpp
  ge_draw_primitive.cpp
)
target_precompile_headers(${ENGINE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/ge_pch.hpp)
target_include_directories(${ENGINE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(${ENGINE_NAME} PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(${ENGINE_NAME} PRIVATE /WX /W4 /wd4305)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${ENGINE_NAME} PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${ENGINE_NAME} PRIVATE glad::glad)

find_package(Stb REQUIRED)
target_include_directories(${ENGINE_NAME} PRIVATE ${Stb_INCLUDE_DIR})