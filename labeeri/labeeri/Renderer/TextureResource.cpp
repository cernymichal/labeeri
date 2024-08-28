#include "TextureResource.h"

#include "Renderer/IRenderer.h"

namespace labeeri {

TextureResource::~TextureResource() {
    if (LAB_RENDERER)
        LAB_RENDERER->deleteTexture(*this);
}

}  // namespace labeeri
