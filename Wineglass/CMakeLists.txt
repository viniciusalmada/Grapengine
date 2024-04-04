# #############################################################################
# Wineglass
add_executable(Wine
  Editor.cpp
  Editor.hpp
  EditorLayer.cpp
  EditorLayer.hpp)

#add_executable(Wine main.cpp)
target_include_directories(Wine PRIVATE SYSTEM
  ${CMAKE_SOURCE_DIR}/Grapengine
  ${CMAKE_SOURCE_DIR}/vendor/imgui
)
target_link_libraries(Wine PRIVATE ${ENGINE_NAME})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(Wine PRIVATE $<$<CONFIG:Release>:/WX> /W4)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(Wine PRIVATE $<$<CONFIG:Release>:-Werror> -Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  target_compile_options(Wine PRIVATE $<$<CONFIG:Release>:-Werror> -Wall -Wextra)
else ()
  message(FATAL_ERROR "Unsupported compiler CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}")
endif ()