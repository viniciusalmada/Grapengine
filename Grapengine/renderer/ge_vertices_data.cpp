#include "ge_vertices_data.hpp"

using namespace GE;

Ptr<VerticesData> VerticesData::Make()
{
  return MakeRef<VerticesData>();
}

void VerticesData::RawPushData(VerticesData&& data)
{
  m_data.insert(m_data.end(), data.m_data.begin(), data.m_data.end());
}

VerticesData::VerticesData() {}

u64 VerticesData::GetSize() const
{
  return m_data.size() * sizeof(VertexStruct);
}

const VertexStruct* VerticesData::GetPtr() const
{
  return m_data.data();
}

BufferLayout VerticesData::GetLayout()
{
  return BufferLayout{ BufferLayout::BuildElementsList({ DataPurpose::POSITION_F3,
                                                         DataPurpose::TEXTURE_COORDINATE_F2,
                                                         DataPurpose::COLOR_F4,
                                                         DataPurpose::NORMAL_F3 }) };
}

std::vector<VertexStruct>& VerticesData::GetData()
{
  return m_data;
}

void VerticesData::Clear()
{
  m_data.clear();
}

void VerticesData::PushVerticesData(VertexStruct&& vs)
{
  m_data.emplace_back(vs);
}

u64 VerticesData::GetCount() const
{
  return m_data.size();
}
