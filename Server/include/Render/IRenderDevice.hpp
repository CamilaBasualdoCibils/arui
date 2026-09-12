#pragma once
#include "Render/IRenderCommandList.hpp"
#include "Render/RenderCommons.hpp"
#include <memory>
namespace ARUI::Render {
class IRenderDevice {
public:
  IRenderDevice() {}
  [[nodiscard]] virtual TextureHandle CreateTexture(const TextureDesc &) = 0;
  [[nodiscard]] virtual BufferHandle CreateBuffer(const BufferDesc &) = 0;
  [[nodiscard]] virtual ShaderModuleHandle
  CreateShaderModule(const ShaderModuleDesc &) = 0;
  [[nodiscard]] virtual GraphicsPipelineHandle CreatePipeline(const GraphicsPipelineDesc &) = 0;
  [[nodiscard]] virtual std::unique_ptr<IRenderCommandList>
  CreateCommandList(QueueType type) = 0;


  virtual void DestroyTexture(TextureHandle) = 0;
  virtual void DestroyBuffer(BufferHandle) = 0;
  virtual void DestroyPipeline(GraphicsPipelineHandle) = 0;
  virtual void DestroyShaderModule(ShaderModuleHandle) = 0;

  virtual RenderCapabilities GetCapabilities() const = 0;

protected:
};
} // namespace ARUI::Render