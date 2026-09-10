#pragma once

#include "Tracker/IXRTracker.hpp"
#include "Views/IViewProvider.hpp"
namespace ARUI {
class SimulatorViewProvider : public IViewProvider {

public:
  void BeginFrame() override {}

  std::span<const RenderView> GetViews() const override {}

  void EndFrame() override {}
};
} // namespace ARUI