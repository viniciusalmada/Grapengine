#ifndef GRAPENGINE_GE_TYPE_UTILS_HPP
#define GRAPENGINE_GE_TYPE_UTILS_HPP

namespace GE
{
  class TypeUtils
  {
  public:
    template <typename Integer>
      requires std::integral<Integer>
    static void* ToVoidPtr(Integer i)
    {
      return reinterpret_cast<void*>(i); // NOLINT(*-pro-type-reinterpret-cast, *-no-int-to-ptr)
    }
  };
}

#endif // GRAPENGINE_GE_TYPE_UTILS_HPP
