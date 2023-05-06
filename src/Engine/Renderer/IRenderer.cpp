#include "IRenderer.h"

namespace labeeri::Engine {

std::unique_ptr<IRenderer> IRenderer::s_renderer = nullptr;

}  // namespace labeeri::Engine
