#pragma once

#include "Engine/API.h"

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
        m_diffuse = vec3(0.37f, 0.65f, 0.78f);
        m_specular = vec3(0.5f);
        m_alpha = 0.6f;
    }

    virtual void bindUniforms() const override;
};

/**
 * @brief TODO
 */
class FlareMaterial : public MaterialResource {
public:
    /**
     * @brief TODO
     */
    explicit FlareMaterial() : MaterialResource(Resources<ShaderResource>::Get("resources/labeeri/shaders/videotexture")) {
    }

    virtual bool opaque() const override {
        return false;
    }

    virtual void bindUniforms() const override;

private:
    Ref<TextureResource> m_texture = loadTexture("resources/labeeri/textures/flare_sequence.png", true, TextureType::Rectangle);
    uvec2 m_size = uvec2(204);
    uvec2 m_count = uvec2(13, 2);
    float m_fps = 24.0f;
};

}  // namespace labeeri
