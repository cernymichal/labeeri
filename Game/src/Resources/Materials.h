#pragma once

/**
 * @brief Water-like material resource.
 */
class WaterMaterial : public ShadedMaterialResource {
public:
    Ref<TextureResource> m_displacementMap = Resources<TextureResource>::Get("textures/perlin512_lin.png");
    f32 m_displacementStrength = 0.1f;
    f32 m_timeMultiplier = 0.015625f;

    explicit WaterMaterial() : ShadedMaterialResource(Resources<ShaderResource>::Get("shaders/water")) {
        m_diffuse = vec3(0.07f, 0.10f, 0.14f);
        m_specular = vec3(0.5f);
        m_alpha = 0.8f;
    }

    virtual void bindUniforms() const override;
};

/**
 * @brief Flare material resource. Uses a videa texture.
 */
class FlareMaterial : public MaterialResource {
public:
    explicit FlareMaterial() : MaterialResource(Resources<ShaderResource>::Get("shaders/flipbook")) {
    }

    virtual bool opaque() const override {
        return false;
    }

    virtual void bindUniforms() const override;

private:
    Ref<TextureResource> m_texture = loadTexture("textures/flare_sequence.png", true, TextureType::Rectangle);
    uvec2 m_size = uvec2(204);
    uvec2 m_count = uvec2(13, 2);
    f32 m_fps = 24.0f;
};
