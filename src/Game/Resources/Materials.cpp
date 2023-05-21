#include "Materials.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri {

void WaterMaterial::bindUniforms() const {
    ShadedMaterialResource::bindUniforms();

    if (m_displacementMap) {
        LAB_RENDERER->bindTexture(TextureType::Texture2D, *m_displacementMap, 5);
        LAB_RENDERER->bindUniform("u_displacement_map", 5);
    }

    LAB_RENDERER->bindUniform("u_displacement_strength", m_displacementStrength);
    LAB_RENDERER->bindUniform("u_time_multiplier", m_timeMultiplier);

    LAB_LOG_RENDERAPI_ERROR();
}

void FlareMaterial::bindUniforms() const {
    LAB_RENDERER->bindTexture(TextureType::Rectangle, *m_texture, 0);
    LAB_RENDERER->bindUniform("u_texture", 0);
    LAB_RENDERER->bindUniform("u_frame_size", m_size);
    LAB_RENDERER->bindUniform("u_frame_count", m_count);
    LAB_RENDERER->bindUniform("u_fps", m_fps);
}

};  // namespace labeeri