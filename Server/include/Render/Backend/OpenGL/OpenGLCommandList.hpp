#pragma once
#include "Render/IRenderCommandList.hpp"
#include <GL/gl.h>
#include <queue>
namespace ARUI::Render {
  class OpenGLRenderDevice;
class OpenGLCommandList : public IRenderCommandList {
public:
OpenGLCommandList(OpenGLRenderDevice* device)
    : renderDevice(device) {}
  void BeginRendering(const RenderPassDesc &desc) override {
    commandQueue.push(BeginRenderCommand{desc});
  }

  void EndRendering() override {
    commandQueue.push(EndRenderCommand{});
  }

  void BindPipeline(GraphicsPipelineHandle handle) override {
    commandQueue.push(BindPipelineCommand{handle});
  }

  void BindVertexBuffer(BufferHandle handle) override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `BindVertexBuffer` is not implemented.");
  }

  void BindIndexBuffer(BufferHandle handle) override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `BindIndexBuffer` is not implemented.");
  }

  void BindTexture(uint32_t slot, TextureHandle handle) override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `BindTexture` is not implemented.");
  }

  void Draw(uint32_t vertexCount) override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `Draw` is not implemented.");
  }

  void DrawIndexed(uint32_t indexCount) override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `DrawIndexed` is not implemented.");
  }

  void Dispatch(uint32_t x, uint32_t y, uint32_t z) override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `Dispatch` is not implemented.");
  }

  OpenGLCommandList() = default;
  ~OpenGLCommandList() = default;

private:
  OpenGLRenderDevice* renderDevice;
  struct BeginRenderCommand {
    RenderPassDesc desc;
  };
  struct EndRenderCommand {};
  struct BindPipelineCommand {
    GraphicsPipelineHandle handle;
  };
  struct DrawCommand {
    uint32_t vertexCount;
  };
  using Command = std::variant<BeginRenderCommand, EndRenderCommand,
                               BindPipelineCommand, DrawCommand>;
  std::queue<Command> commandQueue;
};
} // namespace ARUI::Render