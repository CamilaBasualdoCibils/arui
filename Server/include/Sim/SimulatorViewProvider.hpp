#pragma once

#include "Tracker/IXRTracker.hpp"
#include "Views/IViewProvider.hpp"
#include "Views/RenderView.hpp"
#include <glm/ext/matrix_transform.hpp>
namespace ARUI {
class SimulatorViewProvider : public IViewProvider {

public:
  void BeginFrame() override {}

  std::span<const RenderView> GetViews() const override { return views; }

  void EndFrame() override {}

private:
  std::vector<RenderView> views = {
      RenderView{
          .Name = "DebugCamera",
          .view = glm::lookAt(glm::vec3(2.0f), glm::vec3(0, 1, 0),
                              glm::vec3(0, 1, 0)),
          .projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f,
                                         0.1f, 100.0f),
          .viewportSize = glm::ivec2(800, 600),
      },
      RenderView{.Name = "Head",
                 .view = glm::lookAt(glm::vec3(0, 1.8, 0), glm::vec3(0, 1.8, 1),
                                     glm::vec3(0, 1, 0)),
                 .projection = glm::perspective(glm::radians(45.0f),
                                                800.0f / 600.0f, 0.1f, 100.0f),
                 .viewportSize = glm::ivec2(800, 600)}};
};
} // namespace ARUI