#include "Texture.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

Texture::~Texture() {
    LAB_RENDERER->deleteTexture(*this);
}

}  // namespace labeeri::Engine
