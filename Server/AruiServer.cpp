#include "AruiServer.hpp"
#include "Sim/SimulatorPresenter.hpp"
#include <imgui.h>

int AruiServer::Run() {
  presenter = std::make_shared<ARUI::Sim::SimulatorPresenter>();

  while (!stopRequested) {
    presenter->BeginFrame();

    ImGui::ShowDemoWindow();
    presenter->EndFrame();
  }

  return 0;
}
