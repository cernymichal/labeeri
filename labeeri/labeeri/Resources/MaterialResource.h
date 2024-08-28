#pragma once

#include "Renderer/ShaderResource.h"
#include "Renderer/TextureResource.h"

namespace labeeri {

/**
 * @brief A shared material resource.
 */
class MaterialResource {
public:
    Ref<ShaderResource> m_shader;

    /**
     * @param shader The shader to use for the material.
     */
    explicit MaterialResource(const Ref<ShaderResource>& shader) : m_shader(shader) {
    }

    virtual ~MaterialResource() = default;

    /**
     * @return Whether the material is opaque or not.
     */
    virtual bool opaque() const = 0;

    /**
     * @brief Bind the materials uniforms.
     */
    virtual void bindUniforms() const = 0;
};

/**
 * @brief Non-shaded flat material.
 */
class FlatMaterialResource : public MaterialResource {
public:
    Ref<TextureResource> m_texture = nullptr;
    vec3 m_color = FALLBACK_COLOR;
    f32 m_alpha = 1.0f;

    /**
     * @param shader The shader to use for the material.
     * @param color The color of the material.
     */
    FlatMaterialResource(const Ref<ShaderResource>& shader, const vec3& color)
        : MaterialResource(shader), m_color(color) {
    }

    /**
     * @param shader The shader to use for the material.
     * @param texture The texture of the material.
     */
    FlatMaterialResource(const Ref<ShaderResource>& shader, const Ref<TextureResource>& texture)
        : MaterialResource(shader), m_texture(texture) {
    }

    virtual bool opaque() const override {
        return m_alpha == 1.0f;
    }

    virtual void bindUniforms() const override;
};

/**
 * @brief Phong-shaded material.
 */
class ShadedMaterialResource : public MaterialResource {
public:
    vec3 m_diffuse = FALLBACK_COLOR;
    Ref<TextureResource> m_diffuseMap = nullptr;
    vec3 m_specular = vec3(0.2f);
    Ref<TextureResource> m_specularMap = nullptr;
    f32 m_shininess = 32.0f;
    f32 m_metallic = 0;
    Ref<TextureResource> m_metallicMap = nullptr;
    Ref<TextureResource> m_normalMap = nullptr;
    f32 m_alpha = 1.0f;

    /**
     * @param shader The shader to use for the material.
     */
    explicit ShadedMaterialResource(const Ref<ShaderResource>& shader) : MaterialResource(shader) {
    }

    /**
     * @param shader The shader to use for the material.
     * @param diffuse The diffuse color of the material.
     */
    ShadedMaterialResource(const Ref<ShaderResource>& shader, vec3 diffuse) : ShadedMaterialResource(shader) {
        m_diffuse = diffuse;
    }

    virtual bool opaque() const override {
        return m_alpha == 1.0f;
    }

    virtual void bindUniforms() const override;
};

}  // namespace labeeri
