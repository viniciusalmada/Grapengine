# #############################################################################
# Wineglass
add_executable(Wine
  Editor.cpp
  Editor.hpp
  EditorLayer.cpp
  EditorLayer.hpp
  panels/SceneHierarchyPanel.cpp
  panels/SceneHierarchyPanel.hpp
)

#add_executable(Wine main.cpp)
target_include_directories(Wine PRIVATE SYSTEM
  ${CMAKE_SOURCE_DIR}/Grapengine
  ${CMAKE_SOURCE_DIR}/vendor/imgui
)
target_link_libraries(Wine PRIVATE Grapengine)
target_link_libraries(Wine PRIVATE NativeScripts)
target_link_libraries(Wine PRIVATE GrapengineCompileOptions)