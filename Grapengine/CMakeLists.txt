set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# #############################################################################
# Engine
add_library(Grapengine STATIC
  controllers/ge_app_controller.cpp
  core/ge_application.cpp
  core/ge_platform.cpp
  core/ge_window.cpp
  drawables/ge_canvas.cpp
  drawables/ge_cube.cpp
  drawables/ge_cylinder.cpp
  drawables/ge_drawing_object.cpp
  drawables/ge_mesh.cpp
  drawables/ge_world_reference.cpp
  events/ge_event.cpp
  input/ge_input.cpp
  input/ge_key_codes.cpp
  layer/ge_imgui_layer.cpp
  layer/ge_layer.cpp
  log/ge_logger.cpp
  math/ge_arithmetic.cpp
  math/ge_geometry.cpp
  math/ge_quaternions.cpp
  math/ge_transformations.cpp
  math/ge_vector.cpp
  profiling/ge_time.cpp
  renderer/ge_buffer_layout.cpp
  renderer/ge_camera.cpp
  renderer/ge_editor_camera.cpp
  renderer/ge_framebuffer.cpp
  renderer/ge_gl_checkers.cpp
  renderer/ge_index_buffer.cpp
  renderer/ge_ishader_program.hpp
  renderer/ge_renderer.cpp
  renderer/ge_shader.cpp
  renderer/ge_texture_2d.cpp
  renderer/ge_vertex_array.cpp
  renderer/ge_vertex_buffer.cpp
  renderer/shader_programs/ge_material_shader.cpp
  renderer/shader_programs/ge_pos_tex_shader.cpp
  utils/ge_io.cpp
  utils/ge_random.cpp
  scene/ge_scene.cpp
  scene/ge_scene.hpp
  scene/ge_components.hpp
  scene/ge_ec_registry.cpp
  scene/ge_ec_registry.hpp
  scene/ge_entity.hpp
  core/ge_context.cpp
  core/ge_context.hpp
)
target_precompile_headers(Grapengine PRIVATE ${CMAKE_SOURCE_DIR}/Grapengine/grapengine_pch.hpp)
target_include_directories(Grapengine
  PUBLIC ${CMAKE_SOURCE_DIR}/Grapengine
)

target_compile_definitions(Grapengine PRIVATE
  GLFW_INCLUDE_NONE
  GRAPENGINE_CORE
)

message(STATUS "GRAPENGINE: Setting up platform = ${CMAKE_SYSTEM_NAME}")
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  target_compile_definitions(Grapengine PUBLIC GE_PLATFORM_WINDOWS)
elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_compile_definitions(Grapengine PUBLIC GE_PLATFORM_LINUX)
else ()
  message(FATAL_ERROR "Unsupported platform")
endif ()

target_link_libraries(Grapengine PRIVATE GrapengineCompileOptions)

# ############################################################################
# imgui
file(GLOB IMGUI_SRC ${CMAKE_SOURCE_DIR}/vendor/imgui/*.cpp ${CMAKE_SOURCE_DIR}/imgui/*.h)
add_library(ImGui STATIC
  ${IMGUI_SRC}
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.h
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
  ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.h
  ${CMAKE_SOURCE_DIR}/vendor/imgui/misc/cpp/imgui_stdlib.h
  ${CMAKE_SOURCE_DIR}/vendor/imgui/misc/cpp/imgui_stdlib.cpp
)
set_target_properties(
  ImGui
  PROPERTIES
  CXX_CLANG_TIDY ""
)
target_include_directories(ImGui SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/vendor/imgui)
target_link_libraries(Grapengine PUBLIC ImGui)

# #############################################################################
# Dependencies from VCPKG
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Grapengine PRIVATE glfw)
target_link_libraries(ImGui PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(Grapengine PRIVATE glad::glad)

find_package(Stb REQUIRED)
target_include_directories(Grapengine SYSTEM PRIVATE ${Stb_INCLUDE_DIR})

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(Grapengine PUBLIC spdlog::spdlog_header_only)