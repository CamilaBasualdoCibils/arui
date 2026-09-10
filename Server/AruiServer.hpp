#pragma once

#include "Render/Present/IPresenter.hpp"
#include "Tracker/IXRTracker.hpp"
#include <atomic>
#include <memory>
class AruiServer {

public:
  AruiServer(int argc, char **argv) {}
  int Run();

  //std::shared_ptr<ARUI::IXRTracker> tracker;
  std::shared_ptr<ARUI::IPresenter> presenter;
  std::atomic_bool stopRequested{false};
};