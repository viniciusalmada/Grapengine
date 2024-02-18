#ifndef GRAPENGINE_PCH_HPP
#define GRAPENGINE_PCH_HPP

#include <algorithm>
#include <any>
#include <array>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <ctime>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numbers>
#include <random>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

#ifdef WIN32
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  #include <Windows.h>
  #undef far
  #undef near
#endif

// clang-format off
#include "core/ge_config.hpp"
#include "core/ge_type_aliases.hpp"
#include "core/ge_memory.hpp"
#include "core/ge_macros.hpp"
// clang-format on

#endif
