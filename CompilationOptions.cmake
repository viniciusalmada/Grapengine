add_library(GrapengineCompileOptions INTERFACE)

message(STATUS "GRAPENGINE: Setting up platform = ${CMAKE_CXXSYSTEM_NAME}")
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  target_compile_definitions(Grapengine PUBLIC GE_PLATFORM_WINDOWS)
elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_compile_definitions(Grapengine PUBLIC GE_PLATFORM_LINUX)
else ()
  message(FATAL_ERROR "Unsupported platform")
endif ()

message(STATUS "GRAPENGINE: Setting up compiler flags for ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} (${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})")
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_definitions(GrapengineCompileOptions INTERFACE GE_MSVC_COMPILER)
  target_compile_options(GrapengineCompileOptions INTERFACE
    $<$<CONFIG:Release>:/WX> # Treat warnings as errors
    /Wall                    # Enable most common warnings
    /W4                      # Set warning level 4 (highest warning level)
    /wd4711                  # The compiler performed inlining on the given function
    /wd4820                  # Bytes padding added after
    /wd4625                  # Copy constructor implicitly deleted
    /wd4626                  # Copy assignment operator implicitly deleted
    /wd5026                  # Move constructor operator implicitly deleted
    /wd5027                  # Move assignment operator implicitly deleted
    /wd5039                  # extern C function
    /wd4710                  # not inlined (??)
    /wd4868                  # enforce left-to-right
    /wd5045                  # insert Spectre mitigation
  )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_definitions(GrapengineCompileOptions INTERFACE GE_GCC_COMPILER)
  target_compile_options(GrapengineCompileOptions INTERFACE
    $<$<CONFIG:Release>:-Werror> # Treat warnings as errors
    -Wall                       # Enable most common warnings
    -Wextra                     # Enable extra warnings
    -Wempty-body
    -Wpedantic                  # Issue all the warnings demanded by strict ISO C and ISO C++
    -Wconversion                # Warn for implicit conversions that may change the value
    -Wsign-conversion           # Warn for signed-to-unsigned conversion
    -Wunreachable-code          # Warn if the compiler detects code that will never be executed
    -Wunused                    # Warn about variables or functions that are defined but never used
    -Wunused-parameter          # Warn about unused function parameters
    -Wunused-variable           # Warn about unused variables
    -Wfloat-equal               # Warn if floating-point values are compared for equality
    -Wshadow                    # Warn whenever a local variable shadows another local variable
    -Wuninitialized             # Warn about uninitialized variables
    -Wmaybe-uninitialized       # Warn about variables that may be uninitialized
    -Wunused-label              # Warn when a label is declared but not used
    -Wsuggest-override          # Warn if a function could be marked override
  )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC" OR CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
    target_compile_definitions(GrapengineCompileOptions INTERFACE GE_CLANG_COMPILER)
    target_compile_options(GrapengineCompileOptions INTERFACE
      $<$<CONFIG:Release>:-Werror> # Treat warnings as errors
      -Weverything
      -Wnon-virtual-dtor
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
      -Wno-exit-time-destructors
      -Wno-padded
      -Wno-header-hygiene
    )
  else ()
    message(FATAL_ERROR "Unsupported CLANG frontend (CMAKE_CXX_COMPILER_FRONTEND_VARIANT = ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})")
  endif ()
else ()
  message(FATAL_ERROR "Unsupported compiler (CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID})")
endif ()