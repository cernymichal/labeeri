#pragma once

#include "Engine/API.h"

using namespace labeeri::Engine;

namespace labeeri {

/**
 * @brief TODO
 */
class WaterMaterial : public ShadedMaterialResource {
public:
    Ref<TextureResource> m_displacementMap = Resources<TextureResource>::Get("resources/labeeri/textures/perlin512_lin.png");
    float m_displacementStrength = 0.1f;
    float m_timeMultiplier = 0.015625f;

    /**
     * @brief TODO
     */
    explicit WaterMaterial() : ShadedMaterialResource(Resources<ShaderResource>::Get("resources/labeeri/shaders/water")) {
        m_diffuse = glm::vec3(0.37f, 0.65f, 0.78f);
        m_specular = glm::vec3(0.5f);
        m_alpha = 0.6f;
    }

    virtual void bindUniforms() const override;
};

}  // namespace labeeri
