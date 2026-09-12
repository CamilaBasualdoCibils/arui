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
const std::unordered_map<PrimitiveTopology, GLenum> primitiveTopologyToGLenumMap = {
    {PrimitiveTopology::Points, GL_POINTS},
    {PrimitiveTopology::Lines, GL_LINES},
    {PrimitiveTopology::Triangles, GL_TRIANGLES}};
inline std::optional<GLenum> GetGLPrimitiveTopology(PrimitiveTopology topology) {
  auto it = primitiveTopologyToGLenumMap.find(topology);
  if (it != primitiveTopologyToGLenumMap.end()) {
    return it->second;
  }
  return std::nullopt;
}
   struct GLVertexFormat
    {
      GLenum type;
      GLint componentCount;
      GLboolean normalized;
    };
const std::unordered_map<VertexFormat, GLVertexFormat> vertexFormatToGLenumMap = {
    {VertexFormat::Float, GLVertexFormat{.type = GL_FLOAT, .componentCount = 1, .normalized = GL_FALSE}},
    {VertexFormat::Float2, GLVertexFormat{.type = GL_FLOAT, .componentCount = 2, .normalized = GL_FALSE}},
    {VertexFormat::Float3, GLVertexFormat{.type = GL_FLOAT, .componentCount = 3, .normalized = GL_FALSE}},
    {VertexFormat::Float4, GLVertexFormat{.type = GL_FLOAT, .componentCount = 4, .normalized = GL_FALSE}},
    {VertexFormat::UInt, GLVertexFormat{.type = GL_UNSIGNED_INT, .componentCount = 1, .normalized = GL_FALSE}},
    {VertexFormat::UInt2, GLVertexFormat{.type = GL_UNSIGNED_INT, .componentCount = 2, .normalized = GL_FALSE}},
    {VertexFormat::UInt3, GLVertexFormat{.type = GL_UNSIGNED_INT, .componentCount = 3, .normalized = GL_FALSE}},
    {VertexFormat::UInt4, GLVertexFormat{.type = GL_UNSIGNED_INT, .componentCount = 4, .normalized = GL_FALSE}}};
 
inline std::optional<GLVertexFormat> GetGLVertexFormat(VertexFormat format) {
 
  auto it = vertexFormatToGLenumMap.find(format);
  if (it != vertexFormatToGLenumMap.end()) {
    return it->second;
  }
  return std::nullopt;
}
} // namespace ARUI::Render::OpenGL