# #############################################################################
# Engine
add_library(${ENGINE_NAME} SHARED
  ge_application.cpp
  ge_arithmetic.cpp
  ge_assert.cpp
  ge_buffer_layout.cpp
  ge_camera.cpp
  ge_canvas.cpp
  ge_circle_shape.cpp
  ge_cube.cpp
  ge_cylinder.cpp
  ge_draw_primitive.cpp
  ge_editor_camera.cpp
  ge_event.cpp
  ge_gl_checkers.cpp
  ge_index_buffer.cpp
  ge_input.cpp
  ge_io.cpp
  ge_key_codes.cpp
  ge_layer.cpp
  ge_platform.cpp
  ge_pos_tex_shader.cpp
  ge_random.cpp
  ge_rect_shape.cpp
  ge_renderer.cpp
  ge_shader.cpp
  ge_shaders_library.cpp
  ge_texture_2d.cpp
  ge_transformations.cpp
  ge_vector.cpp
  ge_vertex_array.cpp
  ge_vertex_buffer.cpp
  ge_window.cpp
  ge_world_reference.cpp
)
target_precompile_headers(${ENGINE_NAME} PRIVATE ${ENGINE_INCLUDE}/grapengine_pch.hpp)
target_include_directories(${ENGINE_NAME} PUBLIC ${ENGINE_INCLUDE})
target_compile_definitions(${ENGINE_NAME} PRIVATE
  GLFW_INCLUDE_NONE
  GRAPENGINE_EXPORTS
)

message(STATUS "Setting up platform = ${CMAKE_SYSTEM_NAME}")
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  target_compile_definitions(${ENGINE_NAME} PUBLIC GE_PLATFORM_WINDOWS)
elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_compile_definitions(${ENGINE_NAME} PUBLIC GE_PLATFORM_LINUX)
else ()
  message(FATAL_ERROR "Unsupported platform")
endif ()

message(STATUS "Setting up compiler flags = ${CMAKE_CXX_COMPILER_ID}:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}")
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${ENGINE_NAME} PUBLIC
    /Wall                       # Enable most common warnings
    /W4                         # Set warning level 4 (highest warning level)
    $<$<CONFIG:Release>:/WX>     # Treat warnings as errors
  )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(${ENGINE_NAME} PUBLIC
    -Wall                       # Enable most common warnings
    -Wextra                     # Enable extra warnings
    -Wpedantic                  # Issue all the warnings demanded by strict ISO C and ISO C++
    $<$<CONFIG:Release>:-Werror> # Treat warnings as errors
    -Wconversion                # Warn for implicit conversions that may change the value
    -Wsign-conversion           # Warn for signed-to-unsigned conversion
    -Wunreachable-code          # Warn if the compiler detects code that will never be executed
    -Wunused                    # Warn about variables or functions that are defined but never used
    -Wunused-parameter          # Warn about unused function parameters
    -Wunused-variable           # Warn about unused variables
    -Wfloat-equal               # Warn if floating-point values are compared for equality
    -Wshadow                    # Warn whenever a local variable shadows another local variable
    -Wuninitialized             # Warn about uninitialized variables
    -Wmaybe-uninitialized       # Warn about variables that may be uninitialized
    -Wunused-label              # Warn when a label is declared but not used
    -Wsuggest-override          # Warn if a function could be marked override
    -Wnon-virtual-dtor          # Warn when a class has a non-virtual destructor
  )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC" OR CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
    target_compile_options(${ENGINE_NAME} PUBLIC
      -Wall                       # Enable most warning messages
      -Wextra                     # Enable some extra warning messages
      -Wpedantic                  # Warn about non-portable constructs
      $<$<CONFIG:Release>:-Werror> # Treat warnings as errors
      -Wshadow                    # Warn whenever a local variable shadows another local variable
      -Wconversion                # Warn for implicit conversions that may change the value
      -Wsign-conversion           # Warn for implicit conversions that may change the sign
      -Wformat=2                  # Check printf/scanf format strings
      -Wundef                     # Warn if an undefined identifier is evaluated in an #if directive
      -Wunreachable-code          # Warn if code will never be executed
      -Wunused                    # Warn about unused functions, variables, etc.
    )
  else ()
    message(FATAL_ERROR "Unsupported CLANG frontend (CMAKE_CXX_COMPILER_FRONTEND_VARIANT = ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})")
  endif ()
else ()
  message(FATAL_ERROR "Unsupported compiler (CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID})")
endif ()

# #############################################################################
# Dependencies from VCPKG
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${ENGINE_NAME} PRIVATE glfw)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${ENGINE_NAME} PRIVATE glad::glad)

find_package(Stb REQUIRED)
target_include_directories(${ENGINE_NAME} PRIVATE ${Stb_INCLUDE_DIR})