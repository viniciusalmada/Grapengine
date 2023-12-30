#ifndef GRAPHICENGINE3D_GE_USING_HPP
#define GRAPHICENGINE3D_GE_USING_HPP

#include <cstdint>
#include <memory>

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

/**
 * Pointer that acts as reference
 */
template <class T>
using Ref = std::shared_ptr<T>;

/**
 * Pointer that lives only inside a defined scope
 */
template <class T>
using Scope = std::unique_ptr<T>;

#endif // GRAPHICENGINE3D_GE_USING_HPP
