# #############################################################################
# Scripts
add_library(Scripts STATIC
  CamController.hpp)

target_include_directories(Scripts PRIVATE SYSTEM
  ${CMAKE_SOURCE_DIR}/Grapengine
)
target_link_libraries(Scripts PRIVATE Grapengine)
target_link_libraries(Scripts PRIVATE GrapengineCompileOptions)