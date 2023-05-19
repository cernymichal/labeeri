#pragma once

#include "Engine/Renderer/ShaderResource.h"
#include "Engine/Renderer/TextureResource.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class MaterialResource {
public:
    Ref<ShaderResource> m_shader;

    /**
     * @brief TODO
     */
    explicit MaterialResource(const Ref<ShaderResource>& shader) : m_shader(shader) {
    }

    /**
     * @brief TODO
     */
    virtual ~MaterialResource() = default;

    /**
     * @brief TODO
     */
    virtual bool opaque() const = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniforms() const = 0;
};

/**
 * @brief TODO
 */
class FlatMaterialResource : public MaterialResource {
public:
    Ref<TextureResource> m_texture = nullptr;
    glm::vec3 m_color = FALLBACK_COLOR;
    float m_alpha = 1.0f;

    /**
     * @brief TODO
     */
    FlatMaterialResource(const Ref<ShaderResource>& shader, const glm::vec3& color)
        : MaterialResource(shader), m_color(color) {
    }

    /**
     * @brief TODO
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
 * @brief TODO
 */
class ShadedMaterialResource : public MaterialResource {
public:
    glm::vec3 m_diffuse = FALLBACK_COLOR;
    Ref<TextureResource> m_diffuseMap = nullptr;
    glm::vec3 m_specular = glm::vec3(0.2f);
    Ref<TextureResource> m_specularMap = nullptr;
    float m_shininess = 32.0f;
    float m_metallic = 0;
    Ref<TextureResource> m_metallicMap = nullptr;
    Ref<TextureResource> m_normalMap = nullptr;
    float m_alpha = 1.0f;

    /**
     * @brief TODO
     */
    explicit ShadedMaterialResource(const Ref<ShaderResource>& shader) : MaterialResource(shader) {
    }

    /**
     * @brief TODO
     */
    ShadedMaterialResource(const Ref<ShaderResource>& shader, glm::vec3 diffuse) : ShadedMaterialResource(shader) {
        m_diffuse = diffuse;
    }

    virtual bool opaque() const override {
        return m_alpha == 1.0f;
    }

    virtual void bindUniforms() const override;
};

}  // namespace labeeri::Engine
