#ifndef GRAPHICENGINE3D_GE_MEMORY_HPP
#define GRAPHICENGINE3D_GE_MEMORY_HPP

template <class T, class... Args>
Ref<T> MakeRef(Args... args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <class T, class... Args>
Scope<T> MakeScope(Args... args)
{
  return std::make_unique<T>(std::forward<Args>(args)...);
}

#endif // GRAPHICENGINE3D_GE_MEMORY_HPP
