#include "Framebuffer.h"

#include "Renderer/IRenderer.h"

namespace labeeri {

Framebuffer::~Framebuffer() {
    LAB_RENDERER->deleteFramebuffer(*this);
}

}  // namespace labeeri
