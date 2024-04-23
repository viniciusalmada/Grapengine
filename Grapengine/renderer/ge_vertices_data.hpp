#ifndef GRAPENGINE_VERTICES_DATA_HPP
#define GRAPENGINE_VERTICES_DATA_HPP

#include "core/ge_assert.hpp"
#include "ge_buffer_layout.hpp"
namespace GE
{
  class ObjEvaluator
  {
  public:
    explicit ObjEvaluator(const std::vector<ShaderDataType>& types) : m_types(types) {}

    [[nodiscard]] u64 ValidityPositionToFill() const { return m_validator.size(); }

    [[nodiscard]] ShaderDataType Type(u64 pos) { return m_types[pos]; }

    void PushValue(bool value) { m_validator.push_back(value); }

    [[nodiscard]] bool IsValid() const
    {
      return m_validator.size() == m_types.size() &&
             std::ranges::all_of(m_validator, [](auto&& v) { return v; });
    }

  private:
    std::vector<bool> m_validator;
    std::vector<ShaderDataType> m_types;
  };

  class VerticesData
  {
  public:
    static Ref<VerticesData> Make(const Ref<const BufferLayout>& layout)
    {
      return MakeRef<VerticesData>(layout);
    }

    explicit VerticesData(Ref<const BufferLayout> layout) : m_layout(std::move(layout)) {}

    [[nodiscard]] u64 GetSize() const { return m_data.size(); }

    [[nodiscard]] const void* GetPtr() const { return m_data.data(); }

    [[nodiscard]] Ref<const BufferLayout> GetLayout() const { return m_layout; }

    template <class... T>
    void PushData(T... args);

  private:
    template <class T>
    void EvaluateArgument(T t, ObjEvaluator& objEvaluator);

    template <class T>
    void PushBytes(T arg);

    Ref<const BufferLayout> m_layout;
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
  void VerticesData::EvaluateArgument(T /*unused*/, ObjEvaluator& objEvaluator)
  {
    auto pos = objEvaluator.ValidityPositionToFill();
    bool value = false;
    switch (objEvaluator.Type(pos))
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
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4:
    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:
    case ShaderDataType::Bool:
      break;
    }
    objEvaluator.PushValue(value);
  }

  template <class... T>
  void VerticesData::PushData(T... args)
  {
    ObjEvaluator obj_evaluator{ m_layout->GetTypesSortedList() };
    (..., EvaluateArgument(args, obj_evaluator));
    GE_ASSERT(obj_evaluator.IsValid(), "Some types passed to be push are invalids")
    (..., PushBytes(args));
  }
}
#endif // GRAPENGINE_VERTICES_DATA_HPP
