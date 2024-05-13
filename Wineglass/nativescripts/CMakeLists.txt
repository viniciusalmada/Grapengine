# #############################################################################
# Scripts
add_library(NativeScripts STATIC
  CamController.hpp
  CamController.cpp
)

target_include_directories(NativeScripts PRIVATE SYSTEM
  ${CMAKE_SOURCE_DIR}/Grapengine
)
target_link_libraries(NativeScripts PRIVATE Grapengine)
target_link_libraries(NativeScripts PRIVATE GrapengineCompileOptions)