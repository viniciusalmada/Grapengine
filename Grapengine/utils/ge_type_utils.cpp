#include "ge_type_utils.hpp"

void* GE::TypeUtils::ToVoidPtr(u32 i)
{
  return reinterpret_cast<void*>(i); // NOLINT(*-pro-type-reinterpret-cast, *-no-int-to-ptr)
}

void* GE::TypeUtils::ToVoidPtr(i32 i)
{
  return reinterpret_cast<void*>(i); // NOLINT(*-pro-type-reinterpret-cast, *-no-int-to-ptr)
}
