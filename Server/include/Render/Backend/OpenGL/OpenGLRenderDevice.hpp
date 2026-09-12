#pragma once

#include "Render/Backend/OpenGL/OpenGLCommandList.hpp"
#include "Render/Backend/OpenGL/OpenGLCommons.hpp"
#include "Render/IRenderDevice.hpp"
#include "Render/RenderCommons.hpp"
#include "Sim/SimulatorPresenter.hpp"
#include <GL/glext.h>
#include <atomic>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <variant>
namespace ARUI::Render {
class OpenGLRenderDevice : public IRenderDevice {

  
public:

  OpenGLRenderDevice();
  TextureHandle CreateTexture(const TextureDesc &desc) override;

  BufferHandle CreateBuffer(const BufferDesc &desc) override;

  GraphicsPipelineHandle
  CreatePipeline(const GraphicsPipelineDesc &graphicsDesc) override;

  ShaderModuleHandle CreateShaderModule(const ShaderModuleDesc &desc) override;
  void DestroyPipeline(GraphicsPipelineHandle handle) override;
  void DestroyShaderModule(ShaderModuleHandle handle) override;

  void DestroyTexture(TextureHandle handle) override;

  void DestroyBuffer(BufferHandle) override;

  std::unique_ptr<IRenderCommandList>
  CreateCommandList(QueueType type) override;
  void Submit(const IRenderCommandList &commandList) override;
  RenderCapabilities GetCapabilities() const override { return capabilities; }

    struct GLTexture {
    GLuint id;
  };
    struct GLBuffer {
    GLuint id;
  };
  struct GLShaderModule {
    GLuint id;
  };
    struct GLPipeline {
    GLuint programId;
    GLuint vaoId;
  };
  GLTexture GetGLTexture(TextureHandle handle) const {
    return textures.at(handle);
  }
  GLBuffer GetGLBuffer(BufferHandle handle) const {
    return buffers.at(handle);
  }
  GLShaderModule GetGLShaderModule(ShaderModuleHandle handle) const {
    return shaderModules.at(handle);
  }
  GLPipeline GetGLPipeline(GraphicsPipelineHandle handle) const {
    return pipelines.at(handle);
  }

private:
  const RenderCapabilities capabilities{};
  static RenderCapabilities GetGLCapabilities();


  std::unordered_map<TextureHandle, GLTexture> textures;

  std::unordered_map<BufferHandle, GLBuffer> buffers;
  std::unordered_map<ShaderModuleHandle, GLShaderModule> shaderModules;

  std::unordered_map<GraphicsPipelineHandle, GLPipeline> pipelines;

  std::atomic<TextureHandle> nextTextureHandle{(TextureHandle)1};
  std::atomic<BufferHandle> nextBufferHandle{(BufferHandle)1};
  std::atomic<ShaderModuleHandle> nextShaderModuleHandle{(ShaderModuleHandle)1};
  std::atomic<GraphicsPipelineHandle> nextPipelineHandle{
      (GraphicsPipelineHandle)1};

  TextureHandle GenerateTextureHandle() { return nextTextureHandle++; }
  GraphicsPipelineHandle GeneratePipelineHandle() {
    return nextPipelineHandle++;
  }

  BufferHandle GenerateBufferHandle() { return nextBufferHandle++; }
  ShaderModuleHandle GenerateShaderModuleHandle() {
    return nextShaderModuleHandle++;
  }
  std::shared_ptr<spdlog::logger> logger =
      spdlog::stdout_color_mt("OpenGLRenderDevice");
};


} // namespace ARUI::Render