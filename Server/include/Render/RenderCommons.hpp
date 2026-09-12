#pragma once

#include "Render/RenderEnums.hpp"
#include <cstdint>
#include <glm/glm.hpp>
#include <span>
#include <string_view>
#include <variant>
namespace ARUI::Render {
using TextureHandle = uint64_t;


struct TextureDesc {
  uint32_t width;
  uint32_t height;
  TextureFormat format;
};

struct BufferDesc {
  uint32_t size;
  BufferUsage usage;
};
using BufferHandle = uint64_t;

using ShaderModuleHandle = uint64_t;
struct ShaderModuleDesc {
  ShaderStageFlags stage;

  // Your canonical compiled representation.
  std::span<const std::byte> spirv;

  std::string_view entryPoint = "main";
};
using GraphicsPipelineHandle = uint64_t;
using ComputePipelineHandle = uint64_t;
struct VertexAttribute
{
    uint32_t location;
    uint32_t binding;
    VertexFormat format;
    uint32_t offset;
};

struct VertexBinding
{
    uint32_t binding;
    uint32_t stride;
    bool perInstance = false;
};

struct VertexLayout
{
    std::vector<VertexBinding> bindings;
    std::vector<VertexAttribute> attributes;
};
struct RasterState
{
    CullMode cullMode = CullMode::Back;
    FrontFace frontFace = FrontFace::CounterClockwise;
    PolygonMode polygonMode = PolygonMode::Fill;

    bool depthClamp = false;
};
struct DepthStencilState
{
    bool depthTest = true;
    bool depthWrite = true;

    CompareOp depthCompare = CompareOp::Less;
};
struct BlendAttachmentState
{
    bool enabled = false;

    BlendFactor srcColor = BlendFactor::One;
    BlendFactor dstColor = BlendFactor::Zero;
    BlendOp colorOp = BlendOp::Add;

    BlendFactor srcAlpha = BlendFactor::One;
    BlendFactor dstAlpha = BlendFactor::Zero;
    BlendOp alphaOp = BlendOp::Add;
};

struct BlendState
{
    std::vector<BlendAttachmentState> attachments;
};
struct BindingDesc
{
    uint32_t binding;
    BindingType type;
    ShaderStageFlags stages;
};
struct BindGroupLayoutDesc
{
    std::vector<BindingDesc> bindings;
};
struct GraphicsPipelineDesc
{
    ShaderModuleHandle vertexShader;
    ShaderModuleHandle fragmentShader;

    VertexLayout vertexLayout;

    PrimitiveTopology topology =
        PrimitiveTopology::Triangles;

    RasterState raster{};
    DepthStencilState depthStencil{};
    BlendState blend{};

    std::vector<BindGroupLayoutDesc> bindGroups;

    std::vector<TextureFormat> colorFormats;
    TextureFormat depthFormat =
        TextureFormat::UNDEFINED;

    uint32_t sampleCount = 1;
};
struct ComputePipelineDesc {
  ShaderModuleHandle computeShader;
};
struct RenderPassDesc {
  TextureHandle colorAttachment;
  TextureHandle depthAttachment;

  bool clearColor = false;
  bool clearDepth = false;
  glm::uvec2 dimensions;
  glm::uvec2 offset;
};
struct RenderCapabilities {
  bool multiView = false;
  bool externalMemory = false;
  bool externalSemaphore = false;
  bool fragmentDensityMap = false;
  bool variableRateShading = false;
  bool dmaBuf = false;
};

} // namespace ARUI