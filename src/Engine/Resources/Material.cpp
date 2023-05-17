#include "Material.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

void FlatMaterial::bindUniforms() const {
    bool usingTexture = m_texture != nullptr;

    LAB_RENDERER->bindUniform("u_using_texture", usingTexture);

    if (usingTexture) {
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_texture, 0);
        LAB_RENDERER->bindUniform("u_texture", 0);
    }
    else
        LAB_RENDERER->bindUniform("u_color", m_color);

    LAB_RENDERER->bindUniform("u_alpha", m_alpha);

    LAB_LOG_RENDERAPI_ERROR();
}

void ShadedMaterial::bindUniforms() const {
    bool usingDiffuseMap = m_diffuseMap != nullptr;
    LAB_RENDERER->bindUniform("u_material.using_diffuse_map", usingDiffuseMap);
    if (usingDiffuseMap) {
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_diffuseMap, 0);
        LAB_RENDERER->bindUniform("u_material.diffuse_map", 0);
    }
    else
        LAB_RENDERER->bindUniform("u_material.diffuse", m_diffuse);

    bool usingSpecularMap = m_specularMap != nullptr;
    LAB_RENDERER->bindUniform("u_material.using_specular_map", usingSpecularMap);
    if (usingSpecularMap) {
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_specularMap, 1);
        LAB_RENDERER->bindUniform("u_material.specular_map", 1);
    }
    else
        LAB_RENDERER->bindUniform("u_material.specular", m_specular);

    LAB_RENDERER->bindUniform("u_material.shininess", m_shininess);

    bool usingReflectivnessMap = m_metallicMap != nullptr;
    LAB_RENDERER->bindUniform("u_material.using_metallic_map", usingReflectivnessMap);
    if (usingReflectivnessMap) {
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_metallicMap, 2);
        LAB_RENDERER->bindUniform("u_material.metallic_map", 2);
    }
    else
        LAB_RENDERER->bindUniform("u_material.metallic", m_metallic);

    bool usingNormalMap = m_normalMap != nullptr;
    LAB_RENDERER->bindUniform("u_material.using_normal_map", usingNormalMap);
    if (usingNormalMap) {
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_normalMap, 3);
        LAB_RENDERER->bindUniform("u_material.normal_map", 3);
    }

    LAB_RENDERER->bindUniform("u_alpha", m_alpha);

    LAB_LOG_RENDERAPI_ERROR();
}

}  // namespace labeeri::Engine