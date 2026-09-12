#pragma once

#include "Render/Graph/IRenderGraph.hpp"
#include "fg/FrameGraphResource.hpp"
#include <cstdint>
#include <fg/Blackboard.hpp>
#include <fg/FrameGraph.hpp>
namespace ARUI::Render {

struct ARUI_FGBuffer {
  ARUI_FGBuffer() = default;
  using Desc = GraphBufferDesc;
  void create(const Desc &desc, void *) {}
  void destroy(const Desc &desc, void *) {}
  void preRead(const Desc &desc, uint32_t flags, void *context) {}
  void preWrite(const Desc &desc, uint32_t flags, void *context) {}
};
struct ARUI_FGTexture {
  ARUI_FGTexture() = default;
  using Desc = GraphTextureDesc;
  void create(const Desc &desc, void *) {}
  void destroy(const Desc &desc, void *) {}
  void preRead(const Desc &desc, uint32_t flags, void *context) {}
  void preWrite(const Desc &desc, uint32_t flags, void *context) {}
};
class FGRenderGraph : public IRenderGraph {

public:
  void AddPass(std::string_view name, RenderPassSetup setup,
               RenderPassExecute execute) override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `AddPass` is not implemented.");
  }

  void Compile() override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `Compile` is not implemented.");
  }

  void Execute(IRenderDevice &) override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `Execute` is not implemented.");
  }

private:
  FrameGraph m_FrameGraph;
  FrameGraphBlackboard m_Blackboard;
};
} // namespace ARUI::Render