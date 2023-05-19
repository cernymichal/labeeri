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

};  // namespace labeeri