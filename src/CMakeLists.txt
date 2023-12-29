# #############################################################################
# Engine
add_library(${ENGINE_NAME} SHARED
  ge_application.cpp
  ge_entities.cpp
  ge_event.cpp
  ge_renderer.cpp
  ge_shader.cpp
  ge_transformations.cpp
  ge_vector.cpp
  ge_window.cpp
  ge_texture_2d.cpp
  ge_io.cpp
  ge_shaders_library.cpp
)
target_precompile_headers(${ENGINE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/ge_pch.hpp)
target_include_directories(${ENGINE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${ENGINE_NAME} SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/GLAD/include
    ${CMAKE_SOURCE_DIR}/vendor/stb
    )
target_compile_definitions(${ENGINE_NAME} PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(${ENGINE_NAME} PRIVATE /WX /W4 /wd4305)

target_link_libraries(${ENGINE_NAME}
    PUBLIC glfw)
if (WIN32)
  target_link_libraries(${ENGINE_NAME} PRIVATE opengl32.lib)
elseif (UNIX)
  target_link_libraries(${ENGINE_NAME} PRIVATE GL)
endif (WIN32)