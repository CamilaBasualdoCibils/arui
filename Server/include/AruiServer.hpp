#pragma once

#include "Render/IPresenter.hpp"
#include "Render/RenderGraph.hpp"
#include "Tracker/IXRTracker.hpp"
#include "Render/IRenderDevice.hpp"
#include "Views/IViewProvider.hpp"
#include <atomic>
#include <memory>
namespace ARUI {
class AruiServer {

public:
  AruiServer(int argc, char **argv) {}
  int Run();

  //std::shared_ptr<ARUI::IXRTracker> tracker;
  std::shared_ptr<ARUI::IPresenter> presenter;
  std::shared_ptr<ARUI::IViewProvider> viewProvider;
  std::shared_ptr<ARUI::Render::IRenderDevice> renderDevice;
  std::shared_ptr<ARUI::Render::RenderGraph> renderGraph;
  std::atomic_bool stopRequested{false};
};
} // namespace ARUI