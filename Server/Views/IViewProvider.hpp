#pragma once
#include <Views/RenderView.hpp>
#include <span>

namespace ARUI

{

class IViewProvider {
public:
  virtual ~IViewProvider() = default;

  virtual void BeginFrame() = 0;

  virtual std::span<const RenderView> GetViews() const = 0;

  virtual void EndFrame() = 0;
};
} // namespace ARUI