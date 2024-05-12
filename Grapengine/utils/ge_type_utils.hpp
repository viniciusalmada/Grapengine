#ifndef GRAPENGINE_GE_TYPE_UTILS_HPP
#define GRAPENGINE_GE_TYPE_UTILS_HPP

namespace GE
{
  class TypeUtils
  {
  public:
    static void* ToVoidPtr(u32 i);
    static void* ToVoidPtr(i32 i);
  };
}

#endif // GRAPENGINE_GE_TYPE_UTILS_HPP
