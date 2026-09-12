#pragma once
#include "Render/RenderCommons.hpp"
namespace ARUI::Render {
class IRenderCommandList {
public:
  virtual void BeginRendering(const RenderPassDesc &) = 0;
  virtual void EndRendering() = 0;

  virtual void BindPipeline(GraphicsPipelineHandle) = 0;

  virtual void BindVertexBuffer(BufferHandle) = 0;
  virtual void BindIndexBuffer(BufferHandle) = 0;
  virtual void BindTexture(uint32_t slot, TextureHandle) = 0;

  virtual void Draw(uint32_t vertexCount) = 0;
  virtual void DrawIndexed(uint32_t indexCount) = 0;

  virtual void Dispatch(uint32_t x, uint32_t y, uint32_t z) = 0;
};
} // namespace ARUI::Render