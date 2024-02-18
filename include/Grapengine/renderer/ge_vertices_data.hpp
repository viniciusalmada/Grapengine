#ifndef GRAPENGINE_VERTICES_DATA_HPP
#define GRAPENGINE_VERTICES_DATA_HPP

#include "core/ge_assert.hpp"
#include "ge_buffer_layout.hpp"
namespace GE
{
  struct ObjEvaluator
  {
    std::vector<bool> m_validator;
    std::vector<ShaderDataType> m_types;
  };

  class VerticesData
  {
  public:
    explicit VerticesData(Ref<BufferLayout> layout) : m_layout(std::move(layout)) {}

    [[nodiscard]] u64 GetSize() const { return m_data.size(); }

    [[nodiscard]] const void* GetPtr() const { return m_data.data(); }

    [[nodiscard]] auto GetLayout() const { return m_layout; }

    template <class... T>
    void PushData(T... args);

  private:
    template <class T>
    void EvaluateArgument(T t, ObjEvaluator& objEvaluator);

    template <class T>
    void PushBytes(T arg);

    Ref<BufferLayout> m_layout;
    std::vector<std::byte> m_data;
  };

  template <class T>
  void VerticesData::PushBytes(T arg)
  {
    const auto& bytes = std::bit_cast<std::array<std::byte, sizeof(T)>, T>(arg);
    for (const auto& item : bytes)
      m_data.push_back(item);
  }

  template <class T>
  void VerticesData::EvaluateArgument(T, ObjEvaluator& objEvaluator)
  {
    auto pos = objEvaluator.m_validator.size();
    bool value = false;
    switch (objEvaluator.m_types[pos])
    {
    case ShaderDataType::None:
      if constexpr (std::is_same_v<T, void>)
        value = true;
      break;
    case ShaderDataType::Float:
      if constexpr (std::is_same_v<T, f32>)
        value = true;
      break;
    case ShaderDataType::Float2:
      if constexpr (std::is_same_v<T, Vec2>)
        value = true;
      break;
    case ShaderDataType::Float3:
      if constexpr (std::is_same_v<T, Vec3>)
        value = true;
      break;
    case ShaderDataType::Float4:
      if constexpr (std::is_same_v<T, Vec4>)
        value = true;
      break;
    default:
      value = false;
      break;
    }
    objEvaluator.m_validator.push_back(value);
  }

  template <class... T>
  void VerticesData::PushData(T... args)
  {
    ObjEvaluator obj_evaluator{ {}, m_layout->GetTypesSortedList() };
    (..., EvaluateArgument(args, obj_evaluator));
    Assert(std::ranges::find(obj_evaluator.m_validator, false) == obj_evaluator.m_validator.end(),
           "Some types passed to be push are invalids");
    (..., PushBytes(args));
  }
}
#endif // GRAPENGINE_VERTICES_DATA_HPP
