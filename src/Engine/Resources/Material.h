#pragma once

#include "Engine/Renderer/ShaderProgram.h"
#include "Engine/Renderer/Texture.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Material {
public:
    ShaderProgramRef m_shader;

    /**
     * @brief TODO
     */
    Material(const ShaderProgramRef& shader);

    /**
     * @brief TODO
     */
    virtual ~Material() = default;

    /**
     * @brief TODO
     */
    virtual void bindUniforms() const = 0;
};

using MaterialRef = std::shared_ptr<Material>;

/**
 * @brief TODO
 */
class FlatMaterial : public Material {
public:
    TextureRef m_texture = nullptr;
    glm::vec3 m_color = FALLBACK_COLOR;

    /**
     * @brief TODO
     */
    FlatMaterial(const ShaderProgramRef& shader, const glm::vec3& color = FALLBACK_COLOR);

    /**
     * @brief TODO
     */
    FlatMaterial(const ShaderProgramRef& shader, const TextureRef& texture);

    /**
     * @brief TODO
     */
    virtual void bindUniforms() const override;
};

}  // namespace labeeri::Engine
