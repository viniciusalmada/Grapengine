#include "ge_batch_renderer.hpp"

#include "ge_buffer_handler.hpp"

#include <glad/glad.h>

using namespace GE;

BatchRenderer::BatchRenderer() : m_drawing_objects(), m_vertices_data({}) {}

void BatchRenderer::PushObject(Ptr<IShaderProgram> shader,
                               VerticesData&& vd,
                               const std::vector<u32>& indices,
                               const Mat4& modelMat)
{
  if (!m_vertices_data.contains(shader))
  {
    m_vertices_data.emplace(shader, std::make_pair(VerticesData::Make(), std::vector<u32>{}));
    m_drawing_objects.emplace(shader, DrawingObject{});
  }

  auto& vertices_pair = m_vertices_data.at(shader);

  Ptr<VerticesData> shader_vertices_data = vertices_pair.first;
  BufferHandler::UpdatePosition(vd, modelMat);
  shader_vertices_data->RawPushData(std::move(vd));

  std::vector<u32>& indices_data = vertices_pair.second;
  if (indices_data.empty())
  {
    indices_data.insert(indices_data.end(), indices.begin(), indices.end());
    return;
  }
  const u32 current_max_id = indices_data.empty() ? 0 : std::ranges::max(indices_data);
  indices_data.reserve(indices_data.size() + indices.size());
  std::ranges::for_each(indices, [&](u32 i) { indices_data.push_back(i + current_max_id + 1); });
}

void BatchRenderer::Begin()
{
  for (auto& [shader, vertices_pair] : m_vertices_data)
  {
    vertices_pair.first->Clear();
    vertices_pair.second.clear();
  }
}

void BatchRenderer::End()
{
  for (auto& [shader, vertices_pair] : m_vertices_data)
  {
    shader->Activate();

    m_drawing_objects.at(shader).SetVerticesData(vertices_pair.first);
    m_drawing_objects.at(shader).SetIndicesData(vertices_pair.second);
    Draw(m_drawing_objects.at(shader));
  }
}

void BatchRenderer::Draw(const DrawingObject& drawingObject)
{
  drawingObject.Bind();
  glDrawElements(GL_TRIANGLES, drawingObject.IndicesCount(), GL_UNSIGNED_INT, nullptr);
}
