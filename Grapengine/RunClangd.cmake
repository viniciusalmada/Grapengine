set(BUILD_DIR ${CMAKE_ARGV3})
set(GRAPES_SOURCES ${CMAKE_ARGV4})

message(STATUS "Compile database at ${BUILD_DIR}")

foreach (SRC IN LISTS GRAPES_SOURCES)
  message(STATUS "Analyzing ${SRC}")
  execute_process(
    COMMAND clangd --compile-commands-dir=${BUILD_DIR} --log=error --clang-tidy --check=${SRC}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND_ECHO STDOUT
  )
endforeach ()