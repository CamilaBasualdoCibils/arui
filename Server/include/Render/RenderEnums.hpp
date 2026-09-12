#pragma once
#include <cstdint>
namespace ARUI::Render {

enum class TextureFormat : uint32_t {
  UNDEFINED,
  RGBA8,
  RGB8,
  DEPTH24_STENCIL8
};
enum class BufferUsage : uint32_t {
  VERTEX_BUFFER = 1 << 0,
  INDEX_BUFFER = 1 << 1,
  UNIFORM_BUFFER = 1 << 2
};
enum class QueueType : uint32_t { GRAPHICS, COMPUTE, TRANSFER };
enum class ShaderStageFlags : uint32_t { VERTEX, FRAGMENT, COMPUTE };
enum class PrimitiveTopology { Triangles, TriangleStrip, Lines, Points };

enum class CullMode { None, Front, Back };

enum class FrontFace { Clockwise, CounterClockwise };

enum class PolygonMode { Fill, Line, Point };
enum class CompareOp {
  Never,
  Less,
  LessEqual,
  Equal,
  GreaterEqual,
  Greater,
  NotEqual,
  Always
};
enum class BlendFactor {
  Zero,
  One,
  SrcAlpha,
  OneMinusSrcAlpha,
  DstAlpha,
  OneMinusDstAlpha
};

enum class BlendOp { Add, Subtract, ReverseSubtract, Min, Max };
enum class VertexFormat {
  Float,
  Float2,
  Float3,
  Float4,

  UInt,
  UInt2,
  UInt3,
  UInt4
};
enum class BindingType
{
    UniformBuffer,
    StorageBuffer,
    SampledTexture,
    StorageTexture,
    Sampler
};

} // namespace ARUI::Render