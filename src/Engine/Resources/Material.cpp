#include "Material.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

Material::Material(const ShaderProgramRef& shader) : m_shader(shader) {
}

FlatMaterial::FlatMaterial(const ShaderProgramRef& shader, const glm::vec3& color)
    : Material(shader), m_color(color) {
}

FlatMaterial::FlatMaterial(const ShaderProgramRef& shader, const TextureRef& texture)
    : Material(shader), m_texture(texture) {
}

void FlatMaterial::bindUniforms() const {
    bool usingTexture = m_texture != nullptr;

    LAB_RENDERER->bindUniform("u_using_texture", usingTexture);

    if (usingTexture)
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_texture, 0);
    else
        LAB_RENDERER->bindUniform("u_color", m_color);
}

ShadedMaterial::ShadedMaterial(const ShaderProgramRef& shader) : Material(shader) {
}

void ShadedMaterial::bindUniforms() const {
    bool usingDiffuseMap = m_diffuseMap != nullptr;
    LAB_RENDERER->bindUniform("u_material.using_diffuse_map", usingDiffuseMap);
    if (usingDiffuseMap)
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_diffuseMap, 0);
    else
        LAB_RENDERER->bindUniform("u_material.diffuse", m_diffuse);

    bool usingSpecularMap = m_specularMap != nullptr;
    LAB_RENDERER->bindUniform("u_material.using_specular_map", usingSpecularMap);
    if (usingSpecularMap)
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_specularMap, 1);
    else
        LAB_RENDERER->bindUniform("u_material.specular", m_specular);

    LAB_RENDERER->bindUniform("u_material.shininess", m_shininess);

    bool usingNormalMap = m_normalMap != nullptr;
    LAB_RENDERER->bindUniform("u_material.using_normal_map", usingNormalMap);
    if (usingNormalMap)
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_normalMap, 2);
}

}  // namespace labeeri::Engine