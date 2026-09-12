#include "Render/Backend/OpenGL/OpenGLRenderDevice.hpp"
#include <unordered_set>
static std::unordered_set<std::string> GetGLExtensions() {
  std::unordered_set<std::string> extensions;

  GLint count = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &count);

  for (GLint i = 0; i < count; ++i) {
    const char *ext =
        reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i));

    if (ext)
      extensions.emplace(ext);
  }

  return extensions;
}

static bool HasExtension(const std::unordered_set<std::string> &extensions,
                         std::string_view name) {
  return extensions.contains(std::string{name});
}
ARUI::Render::OpenGLRenderDevice::OpenGLRenderDevice()
    : IRenderDevice() {}

ARUI::Render::RenderCapabilities ARUI::Render::OpenGLRenderDevice::GetGLCapabilities() {
  const auto extensions = GetGLExtensions();

  RenderCapabilities caps{};

  caps.multiView = HasExtension(extensions, "GL_OVR_multiview") ||
                   HasExtension(extensions, "GL_OVR_multiview2");

  caps.externalMemory = HasExtension(extensions, "GL_EXT_memory_object");

  caps.externalSemaphore = HasExtension(extensions, "GL_EXT_semaphore");

  caps.fragmentDensityMap = false; // No direct standard OpenGL equivalent.

  caps.variableRateShading =
      HasExtension(extensions, "GL_NV_shading_rate_image");

  caps.dmaBuf =
      false; // This is normally an EGL capability, not a GL capability.

  return caps;
}
