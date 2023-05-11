#pragma once

#include "Engine/Renderer/ShaderProgram.h"
#include "Engine/Renderer/Texture.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Material {
public:
    Ref<ShaderProgram> m_shader;

    /**
     * @brief TODO
     */
    explicit Material(const Ref<ShaderProgram>& shader) : m_shader(shader) {
    }

    /**
     * @brief TODO
     */
    virtual ~Material() = default;

    /**
     * @brief TODO
     */
    virtual void bindUniforms() const = 0;
};

/**
 * @brief TODO
 */
class FlatMaterial : public Material {
public:
    Ref<Texture> m_texture = nullptr;
    glm::vec3 m_color = FALLBACK_COLOR;

    /**
     * @brief TODO
     */
    FlatMaterial(const Ref<ShaderProgram>& shader, const glm::vec3& color)
        : Material(shader), m_color(color) {
    }

    /**
     * @brief TODO
     */
    FlatMaterial(const Ref<ShaderProgram>& shader, const Ref<Texture>& texture)
        : Material(shader), m_texture(texture) {
    }

    /**
     * @brief TODO
     */
    virtual void bindUniforms() const override;
};

/**
 * @brief TODO
 */
class ShadedMaterial : public Material {
public:
    glm::vec3 m_diffuse = FALLBACK_COLOR;
    Ref<Texture> m_diffuseMap = nullptr;
    glm::vec3 m_specular = glm::vec3(0.2f);
    Ref<Texture> m_specularMap = nullptr;
    float m_shininess = 32.0f;
    Ref<Texture> m_normalMap = nullptr;

    /**
     * @brief TODO
     */
    explicit ShadedMaterial(const Ref<ShaderProgram>& shader) : Material(shader) {
    }

    /**
     * @brief TODO
     */
    ShadedMaterial(const Ref<ShaderProgram>& shader, glm::vec3 diffuse) : ShadedMaterial(shader) {
        m_diffuse = diffuse;
    }

    /**
     * @brief TODO
     */
    virtual void bindUniforms() const override;
};

}  // namespace labeeri::Engine
