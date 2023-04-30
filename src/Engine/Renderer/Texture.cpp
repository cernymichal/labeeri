#include "Texture.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

Texture::Texture(LAB_GL_HANDLE texture) : m_texture(texture) {
}

Texture::Texture(Texture&& other) noexcept : m_texture(other.m_texture) {
    other.m_texture = 0;
}

Texture::~Texture() {
    LAB_RENDERER->deleteTexture(*this);
}

Texture::operator LAB_GL_HANDLE() const {
    return m_texture;
}

}  // namespace labeeri::Engine
