#ifndef GRAPENGINE_GE_TYPE_UTILS_HPP
#define GRAPENGINE_GE_TYPE_UTILS_HPP

namespace GE
{
  class TypeUtils
  {
  public:
#if defined(GE_MSVC_COMPILER)
  #pragma warning(push)
  #pragma warning(disable : 4312) // conversion from 'Integer' to 'void *' of greater size
#endif
    template <typename Integer>
      requires std::integral<Integer>
    static void* ToVoidPtr(Integer i)
    {
      return reinterpret_cast<void*>(i); // NOLINT(*-pro-type-reinterpret-cast, *-no-int-to-ptr)
    }
#if defined(GE_MSVC_COMPILER)
  #pragma warning(pop)
#endif
  };
}

#endif // GRAPENGINE_GE_TYPE_UTILS_HPP
