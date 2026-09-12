#include "AruiServer.hpp"
#include "Render/Backend/OpenGL/OpenGLCommons.hpp"
#include "Render/Backend/OpenGL/OpenGLRenderDevice.hpp"
#include "Render/Backend/Vulkan/VulkanRenderDevice.hpp"
#include "Render/RenderCommons.hpp"
#include "Render/RenderEnums.hpp"
#include "ShaderRegistry.hpp"
#include "Sim/SimulatorPresenter.hpp"
#include "test_frag.hpp"
#include "test_vert.hpp"
#include <imgui.h>
#include <implot.h>
#include <span>

int ARUI::AruiServer::Run() {
  presenter = std::make_shared<Sim::SimulatorPresenter>();

  // renderDevice =
  // std::make_shared<ARUI::Render::VulkanRenderDevice>(presenter);
  renderDevice = std::make_shared<Render::OpenGLRenderDevice>();
  const auto vertShader = ARUI::Shaders::OpenGL::GetShader("test.vert");
  const auto fragShader = ARUI::Shaders::OpenGL::GetShader("test.frag");
  const Render::ShaderModuleHandle vertShaderModule =
      renderDevice->CreateShaderModule(Render::ShaderModuleDesc{
          .stage = Render::ShaderStageFlags::VERTEX,
          .spirv{std::as_bytes(
              std::span(vertShader.data(), vertShader.wordCount()))}});
  const Render::ShaderModuleHandle fragShaderModule =
      renderDevice->CreateShaderModule(Render::ShaderModuleDesc{
          .stage = Render::ShaderStageFlags::FRAGMENT,
          .spirv{std::as_bytes(
              std::span(fragShader.data(), fragShader.wordCount()))}});

  const Render::GraphicsPipelineHandle pipeline = renderDevice->CreatePipeline(
      Render::GraphicsPipelineDesc{.vertexShader = vertShaderModule,
                                   .fragmentShader = fragShaderModule});

  auto commandList =
      renderDevice->CreateCommandList(Render::QueueType::GRAPHICS);
  commandList->BeginRendering(
      Render::RenderPassDesc{.extent = {800, 600}, .offset = {0, 0}});
  commandList->BindPipeline(pipeline);
  commandList->Draw(Render::PrimitiveTopology::Triangles, 0, 3);
  commandList->EndRendering();
  while (!stopRequested) {
    presenter->BeginFrame();
    renderDevice->Submit(*commandList);
    presenter->EndFrame();
  }

  return 0;
}
