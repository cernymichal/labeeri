#include "Framebuffer.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

Framebuffer::~Framebuffer() {
    LAB_RENDERER->deleteFramebuffer(*this);
}

}  // namespace labeeri::Engine
