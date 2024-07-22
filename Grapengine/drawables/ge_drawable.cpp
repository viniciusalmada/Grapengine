#include "ge_drawable.hpp"

#include "renderer/ge_ishader_program.hpp"

using namespace GE;

Drawable::Drawable(const VerticesData& vertices, const std::vector<u32>& indices) :
    m_vertices_data(vertices), m_indices_data(indices)
{
}

void Drawable::UpdateColor(const Color& color)
{
  for (auto& v : m_vertices_data.GetData())
    v.color = color.ToVec4();
}

const VerticesData& Drawable::GetVerticesData() const
{
  return m_vertices_data;
}

const std::vector<u32>& Drawable::GetIndicesData() const
{
  return m_indices_data;
}
