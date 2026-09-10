#pragma once

#include "Render/Present/IPresenter.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <stdexcept>
namespace ARUI::Sim {
class SimulatorPresenter : public IPresenter {
public:
  void BeginFrame() override;

  void Present(const RenderView &view, RenderTargetHandle target) override;

  void EndFrame() override;

  SimulatorPresenter();
  ~SimulatorPresenter();

private:
  GLFWwindow *window;
  std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("Simulator-Presenter");
};
} // namespace ARUI::Sim