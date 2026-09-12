#include "Render/Backend/OpenGL/OpenGLCommandList.hpp"
#include "Render/Backend/OpenGL/OpenGLCommons.hpp"
#include "Render/Backend/OpenGL/OpenGLRenderDevice.hpp"

void ARUI::Render::OpenGLCommandList::BeginRenderCommand::Execute(
    OpenGLRenderDevice *renderDevice) {
  // Implement the execution logic for beginning a render pass.
  glViewport(desc.offset.x, desc.offset.y, desc.extent.x, desc.extent.y);
}
void ARUI::Render::OpenGLCommandList::EndRenderCommand::Execute(
    OpenGLRenderDevice *renderDevice) {
  // Implement the execution logic for ending a render pass.
}
void ARUI::Render::OpenGLCommandList::BindPipelineCommand::Execute(
    OpenGLRenderDevice *renderDevice) {
  glBindVertexArray(renderDevice->GetGLPipeline(handle).vaoId);
  glUseProgram(renderDevice->GetGLPipeline(handle).programId);
  // Implement the execution logic for binding a pipeline.
}
void ARUI::Render::OpenGLCommandList::DrawCommand::Execute(
    OpenGLRenderDevice *renderDevice) {
  std::optional<GLenum> primitive =
      ARUI::Render::OpenGL::GetGLPrimitiveTopology(topology);
  if (primitive.has_value()) {

    glDrawArraysInstancedBaseInstance(primitive.value(), vertexCount,
                                      firstVertex, instanceCount,
                                      firstInstance);
  } else {
    assert(false && "Invalid primitive topology.");
  }
  // Implement the execution logic for drawing.
}
