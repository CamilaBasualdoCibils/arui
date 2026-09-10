#pragma once

#include "Render/RenderTargetHandle.hpp"
#include "Views/RenderView.hpp"
namespace ARUI {
class IPresenter {
public:
  virtual ~IPresenter() = default;

  virtual void BeginFrame() = 0;

  virtual void Present(const RenderView &view, RenderTargetHandle target) = 0;

  virtual void EndFrame() = 0;
};
} // namespace ARUI