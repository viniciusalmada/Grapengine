#ifndef GRAPHICENGINE3D_GE_MEMORY_MONITOR_HPP
#define GRAPHICENGINE3D_GE_MEMORY_MONITOR_HPP

#include "ge_system.hpp"
#include "ge_using.hpp"

class Mem
{
public:
  GE3D static void RegisterMemoryAllocation(void* ptr, const char* name, u64 size);
  GE3D static void RegisterMemoryDeallocation(void* ptr);
  GE3D static u64 GetAllocatedAmount();
  GE3D static void WriteMemMap();
};
// static void RegisterMemoryDeallocation(void* ptr);

#endif // GRAPHICENGINE3D_GE_MEMORY_MONITOR_HPP
