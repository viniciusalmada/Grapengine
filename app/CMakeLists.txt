# #############################################################################
# App
add_executable(Application main.cpp)
target_include_directories(Application PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Application PRIVATE ${ENGINE_NAME})

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  target_compile_options(Application PRIVATE $<$<CONFIG:Release>:/WX> /W4)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  target_compile_options(Application PRIVATE $<$<CONFIG:Release>:-Werror> -Wall)
else ()
  message(FATAL_ERROR "No supported compiler! ${CMAKE_CXX_COMPILER_ID}")
endif ()