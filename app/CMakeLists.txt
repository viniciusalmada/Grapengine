# #############################################################################
# App
add_executable(Application main.cpp)
target_include_directories(Application PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Application PRIVATE ${ENGINE_NAME})

target_compile_options(Application PRIVATE $<$<CONFIG:Release>:/WX> /W4)