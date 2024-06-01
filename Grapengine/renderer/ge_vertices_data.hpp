#ifndef GRAPENGINE_VERTICES_DATA_HPP
#define GRAPENGINE_VERTICES_DATA_HPP

#include "ge_buffer_layout.hpp"
#include "renderer/ge_ishader_program.hpp"

namespace GE
{
  class VerticesData
  {
  public:
    static Ptr<VerticesData> Make();

    [[nodiscard]] static BufferLayout GetLayout();

    explicit VerticesData();

    void PushVerticesData(VertexStruct&& vs);

    [[nodiscard]] u64 GetSize() const;

    [[nodiscard]] u64 GetCount() const;

    [[nodiscard]] const VertexStruct* GetPtr() const;

    void RawPushData(VerticesData&& data);

    void Clear();

    std::vector<VertexStruct>& GetData();

  private:
    std::vector<VertexStruct> m_data;
  };
}
#endif // GRAPENGINE_VERTICES_DATA_HPP
