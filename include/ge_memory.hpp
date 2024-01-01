#ifndef GRAPHICENGINE3D_GE_MEMORY_HPP
#define GRAPHICENGINE3D_GE_MEMORY_HPP

#include "ge_memory_monitor.hpp"
#include "ge_using.hpp"

void* operator new(u64 size);
void operator delete (void* ptr)noexcept;


template <class T, class... Args>
Ref<T> MakeRef(Args... args)
{
  auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
  Mem::RegisterMemoryAllocation(ptr.get(), typeid(T).name(), sizeof(T));
  return ptr;
}

template <class T, class... Args>
Scope<T> MakeScope(Args... args)
{
  auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
  Mem::RegisterMemoryAllocation(ptr.get(), typeid(T).name(), sizeof(T));
  return ptr;
}

#endif // GRAPHICENGINE3D_GE_MEMORY_HPP
