set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# #############################################################################
# Engine
file(GLOB_RECURSE GRAPENGINE_SOURCES
  controllers/*.cpp controllers/*.hpp
  core/*.cpp core/*.hpp
  drawables/*.cpp drawables/*.hpp
  events/*.cpp events/*.hpp
  input/*.cpp input/*.hpp
  layer/*.cpp layer/*.hpp
  log/*.cpp log/*.hpp
  math/*.cpp math/*.hpp
  profiling/*.cpp profiling/*.hpp
  renderer/*.cpp renderer/*.hpp
  scene/*.cpp scene/*.hpp
  utils/*.cpp utils/*.hpp
)

add_library(Grapengine STATIC ${GRAPENGINE_SOURCES})
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