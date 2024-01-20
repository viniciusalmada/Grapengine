cmake_minimum_required(VERSION 3.24)
project(Grapengine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(ENGINE_NAME Grapengine)
set(ENGINE_INCLUDE ${CMAKE_SOURCE_DIR}/include/Grapengine)

# #############################################################################
# Engine
add_subdirectory(src)

# #############################################################################
# App
add_subdirectory(app)

# #############################################################################
# Tests
add_subdirectory(tests)