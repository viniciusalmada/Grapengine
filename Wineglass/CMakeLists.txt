# #############################################################################
# App
add_executable(Application main.cpp)
target_include_directories(Application PRIVATE SYSTEM
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/imgui
)
target_link_libraries(Application PRIVATE ${ENGINE_NAME})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(Application PRIVATE $<$<CONFIG:Release>:/WX> /W4)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(Application PRIVATE $<$<CONFIG:Release>:-Werror> -Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  target_compile_options(Application PRIVATE $<$<CONFIG:Release>:-Werror> -Wall -Wextra)
else ()
  message(FATAL_ERROR "Unsupported compiler CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}")
endif ()