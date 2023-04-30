#include "Material.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

Material::Material(const ShaderProgramRef& shader) : m_shader(shader) {
}

FlatMaterial::FlatMaterial(const ShaderProgramRef& shader, const glm::vec3& color)
    : Material(shader), m_color(color), m_texture(nullptr) {
}

FlatMaterial::FlatMaterial(const ShaderProgramRef& shader, const TextureRef& texture)
    : Material(shader), m_color(FALLBACK_COLOR), m_texture(texture) {
}

void FlatMaterial::bindUniforms() const {
    bool usingTexture = m_texture != nullptr;

    LAB_RENDERER->bindUniform("u_using_texture", usingTexture);

    if (usingTexture)
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_texture);
    else
        LAB_RENDERER->bindUniform("u_color", m_color);
}

}  // namespace labeeri::Engine