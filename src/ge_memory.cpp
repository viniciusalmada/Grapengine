
#include "ge_memory.hpp"

#include <ge_memory_monitor.hpp>

void* operator new(u64 size)
{
  return malloc(size);
}

void operator delete(void* ptr) noexcept
{
  Mem::RegisterMemoryDeallocation(ptr);
  free(ptr);
}

struct MemInfo
{
  std::string name;
  u64 size;
};

struct MemoryMap
{
  std::list<std::pair<void*, MemInfo>> memory_map{};
  //  void Print() const
  //  {
  //    for (const auto& [ptr, str] : memory_map)
  //      std::cout << ptr << " -> " << str << std::endl;
  //  }
};

static MemoryMap mm{};

void Mem::RegisterMemoryAllocation(void* ptr, const char* name, u64 size)
{
  mm.memory_map.emplace_back(ptr, MemInfo{ name, size });
}

void Mem::RegisterMemoryDeallocation(void* ptr)
{
  erase_if(mm.memory_map, [ptr](auto&& m) { return m.first == ptr; });
}

u64 Mem::GetAllocatedAmount()
{
  const u64 sum = std::reduce(std::begin(mm.memory_map),
                              std::end(mm.memory_map),
                              u64{},
                              [](u64 s, auto&& p) { return s + p.second.size; });
  return sum;
}

void Mem::WriteMemMap()
{
  std::ofstream out{ "memory_map.txt" };
  for (const auto& [ptr, info] : mm.memory_map)
  {
    out << ptr << "-> " << info.size << " (" << info.name << ")\n";
  }
}
