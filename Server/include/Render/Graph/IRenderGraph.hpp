#pragma once

#include "Render/IRenderDevice.hpp"
#include "Render/RenderCommons.hpp"
#include <cstdint>
#include <string_view>
namespace ARUI::Render {
using GraphTextureHandle = uint32_t;
using GraphBufferHandle = uint32_t;
using GraphTextureDesc = TextureDesc;
using GraphBufferDesc = BufferDesc;
class RenderGraphBuilder;
class RenderGraphContext;
using RenderPassSetup = std::function<void(RenderGraphBuilder &)>;
using RenderPassExecute = std::function<void(RenderGraphContext &)>;
class IRenderGraph {
public:
  class RenderGraphBuilder {
    virtual GraphTextureHandle CreateTexture(std::string_view name,
                                             const GraphTextureDesc &) = 0;
    virtual GraphBufferHandle CreateBuffer(std::string_view name,
                                           const GraphBufferDesc &) = 0;
  };
  virtual GraphTextureHandle CreateTexture(std::string_view name,
                                           const GraphTextureDesc &) = 0;

  virtual GraphBufferHandle CreateBuffer(std::string_view name,
                                         const GraphBufferDesc &) = 0;

  virtual void AddPass(std::string_view name, RenderPassSetup setup,
                       RenderPassExecute execute) = 0;

  virtual void Compile() = 0;
  virtual void Execute(IRenderDevice &) = 0;
};
} // namespace ARUI::Render