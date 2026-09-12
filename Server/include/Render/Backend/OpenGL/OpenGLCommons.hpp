#pragma once

#include "Render/RenderEnums.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <optional>
#include <unordered_map>
namespace ARUI::Render::OpenGL {
const std::unordered_map<TextureFormat, GLenum> textureFormatToGLenumMap = {
    {TextureFormat::RGBA8, GL_RGBA8},
    {TextureFormat::RGB8, GL_RGB8},
    {TextureFormat::DEPTH24_STENCIL8, GL_DEPTH24_STENCIL8}};
inline std::optional<GLenum> GetGLTextureFormat(TextureFormat format) {
  auto it = textureFormatToGLenumMap.find(format);
  if (it != textureFormatToGLenumMap.end()) {
    return it->second;
  }
  return std::nullopt;
}
const std::unordered_map<BufferUsage, GLenum> bufferUsageToGLenumMap = {
    {BufferUsage::VERTEX_BUFFER, GL_ARRAY_BUFFER},
    {BufferUsage::INDEX_BUFFER, GL_ELEMENT_ARRAY_BUFFER},
    {BufferUsage::UNIFORM_BUFFER, GL_UNIFORM_BUFFER}};
inline std::optional<GLenum> GetGLBufferUsage(BufferUsage usage) {
  auto it = bufferUsageToGLenumMap.find(usage);
  if (it != bufferUsageToGLenumMap.end()) {
    return it->second;
  }
  return std::nullopt;
}
inline bool BufferUsageBitsToGl(BufferUsage usage, GLenum &glUsage) {
  glUsage = 0;
  for (const auto &usagePair : bufferUsageToGLenumMap) {
    if ((uint32_t)usage & (uint32_t)usagePair.first) {
      glUsage |= usagePair.second;
    }
  }
  return glUsage != 0;
}
const std::unordered_map<ShaderStageFlags, GLenum> shaderStageToGLenumMap = {
    {ShaderStageFlags::VERTEX, GL_VERTEX_SHADER},
    {ShaderStageFlags::FRAGMENT, GL_FRAGMENT_SHADER},
    {ShaderStageFlags::COMPUTE, GL_COMPUTE_SHADER}};
inline std::optional<GLenum> GetGLShaderStage(ShaderStageFlags stage) {
  auto it = shaderStageToGLenumMap.find(stage);
  if (it != shaderStageToGLenumMap.end()) {
    return it->second;
  }
  return std::nullopt;
}

} // namespace ARUI::Render::OpenGL