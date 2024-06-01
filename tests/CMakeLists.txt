enable_testing()

file(GLOB_RECURSE TestsSources ${CMAKE_SOURCE_DIR}/tests/*.cpp)

add_executable(EngineTests
        ${TestsSources}
)
target_precompile_headers(EngineTests PRIVATE tests_pch.hpp)
find_package(GTest CONFIG REQUIRED)
target_link_libraries(EngineTests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

target_include_directories(EngineTests PRIVATE ${ENGINE_INCLUDE})

target_link_libraries(EngineTests
        PRIVATE Grapengine
        PRIVATE GrapengineCompileOptions
)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(EngineTests PRIVATE glfw)