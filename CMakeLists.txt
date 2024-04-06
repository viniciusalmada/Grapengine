cmake_minimum_required(VERSION 3.24)

if (NOT DEFINED ${CMAKE_TOOLCHAIN_FILE})
  message(STATUS "Defining vcpkg as toolchain file")
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake)
  message(STATUS ${CMAKE_TOOLCHAIN_FILE})
endif ()

project(Grapengine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ENGINE_NAME Grapengine)
set(ENGINE_INCLUDE ${CMAKE_SOURCE_DIR}/Grapengine)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always -fansi-escape-codes)
  endif ()
endif ()

include(CompilationOptions.cmake)

# #############################################################################
# Engine
add_subdirectory(Grapengine)

# #############################################################################
# App
add_subdirectory(Wineglass)

# #############################################################################
# Tests
add_subdirectory(Grapengine/tests)