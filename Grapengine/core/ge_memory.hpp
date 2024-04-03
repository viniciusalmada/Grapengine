#ifndef GRAPENGINE_MEMORY_HPP
#define GRAPENGINE_MEMORY_HPP

#include "ge_type_aliases.hpp"

namespace GE
{
  template <class T, class... Args>
  Ref<T> MakeRef(Args... args)
  {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }

  template <class T>
  Weak<T> MakeWeak(Ref<T> ref)
  {
    return std::weak_ptr<T>(ref);
  }

  template <class T, class... Args>
  Scope<T> MakeScope(Args... args)
  {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }
}

#endif // GRAPENGINE_MEMORY_HPP
