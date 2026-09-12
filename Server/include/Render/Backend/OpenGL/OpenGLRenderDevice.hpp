#pragma once

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
  TextureHandle CreateTexture(const TextureDesc &desc) override {
    GLTexture glTexture;
    glCreateTextures(GL_TEXTURE_2D, 1, &glTexture.id);
    std::optional<GLenum> glFormat = OpenGL::GetGLTextureFormat(desc.format);
    assert(glFormat.has_value());
    glTextureStorage2D(GL_TEXTURE_2D, 1, glFormat.value(), desc.width,
                       desc.height);
    TextureHandle handle = GenerateTextureHandle();
    textures[handle] = glTexture;
    return handle;
  }

  BufferHandle CreateBuffer(const BufferDesc &desc) override {
    // TODO: Implement this pure virtual method.
    GLBuffer glBuffer;
    glCreateBuffers(1, &glBuffer.id);
    // for every bit in BufferUsage, map it to the corresponding GLenum using
    // bufferUsageToGLenum
    GLenum usage = 0;

    bool success = OpenGL::BufferUsageBitsToGl(desc.usage, usage);
    assert(success);
    glBufferStorage(GL_ARRAY_BUFFER, desc.size, nullptr, usage);
    BufferHandle handle = GenerateBufferHandle();
    buffers[handle] = glBuffer;
    return handle;
  }

  GraphicsPipelineHandle
  CreatePipeline(const GraphicsPipelineDesc &graphicsDesc) override {
    GLuint program = glCreateProgram();
    glAttachShader(program, graphicsDesc.vertexShader);
    glAttachShader(program, graphicsDesc.fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);
    bool linked = false;
    glGetProgramiv(program, GL_LINK_STATUS, reinterpret_cast<GLint *>(&linked));
    if (!linked) {
      GLint infoLogLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
      if (infoLogLength > 0) {
        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(program, infoLogLength, nullptr, infoLog.data());
        logger->error("Program link error: {}", infoLog.data());

        throw std::runtime_error("Failed to link OpenGL program. This should "
                                 "be replaced with a default error shader");
      }
    }
    GraphicsPipelineHandle handle = GeneratePipelineHandle();
    GLPipeline glPipeline{
        .id = program,
    };
    pipelines[handle] = glPipeline;
    return handle;
  }

  ShaderModuleHandle CreateShaderModule(const ShaderModuleDesc& desc) override
{
    const auto glShaderType = OpenGL::GetGLShaderStage(desc.stage);
    assert(glShaderType.has_value());

    GLuint shader = glCreateShader(*glShaderType);

    glShaderBinary(
        1,
        &shader,
        GL_SHADER_BINARY_FORMAT_SPIR_V,
        desc.spirv.data(),
        static_cast<GLsizei>(desc.spirv.size())
    );

    // SPIR-V must be specialized before it is considered compiled.
    glSpecializeShader(
        shader,
        "main",   // SPIR-V entry point
        0,
        nullptr,
        nullptr
    );

    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (compiled != GL_TRUE)
    {
        GLint infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 0)
        {
            std::vector<GLchar> infoLog(infoLogLength);
            glGetShaderInfoLog(
                shader,
                infoLogLength,
                nullptr,
                infoLog.data()
            );

            logger->error("Shader compile error: {}", infoLog.data());
        }

        glDeleteShader(shader);
        throw std::runtime_error("Failed to compile OpenGL SPIR-V shader.");
    }

    const ShaderModuleHandle handle = GenerateShaderModuleHandle();
    shaderModules[handle] = shader;

    return handle;
}
  void DestroyPipeline(GraphicsPipelineHandle handle) override {

    glDeleteProgram(pipelines[handle].id);
    pipelines.erase(handle);
  }
  void DestroyShaderModule(ShaderModuleHandle handle) override {
    glDeleteShader(shaderModules[handle]);
    shaderModules.erase(handle);
  }

  void DestroyTexture(TextureHandle handle) override {
    glDeleteTextures(1, &textures[handle].id);
    textures.erase(handle);
  }

  void DestroyBuffer(BufferHandle) override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `DestroyBuffer` is not implemented.");
  }

  std::unique_ptr<IRenderCommandList>
  CreateCommandList(QueueType type) override {
    // TODO: Implement this pure virtual method.
    assert(false && "Method `CreateCommandList` is not implemented.");
  }
  RenderCapabilities GetCapabilities() const override { return capabilities; }

private:
  const RenderCapabilities capabilities{};
  static RenderCapabilities GetGLCapabilities();

  struct GLTexture {
    GLuint id;
  };
  std::unordered_map<TextureHandle, GLTexture> textures;
  struct GLBuffer {
    GLuint id;
  };
  std::unordered_map<BufferHandle, GLBuffer> buffers;
  std::unordered_map<ShaderModuleHandle, GLuint> shaderModules;
  struct GLPipeline {
    GLuint id;
  };
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