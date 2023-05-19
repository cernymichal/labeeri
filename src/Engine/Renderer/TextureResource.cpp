#include "TextureResource.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

TextureResource::~TextureResource() {
    LAB_RENDERER->deleteTexture(*this);
}

}  // namespace labeeri::Engine
