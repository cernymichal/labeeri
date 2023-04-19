#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>

/**
 * @brief TODO
 */
class ShaderProgram {
public:
    /**
     * @brief TODO
     */
    ShaderProgram(GLuint program);

    ShaderProgram(const ShaderProgram&) = delete;

    /**
     * @brief TODO
     */
    ShaderProgram(ShaderProgram&& other) noexcept;

    /**
     * @brief TODO
     */
    ~ShaderProgram();

    /**
     * @brief TODO
     */
    GLint getUniformLocation(const char* name);

    /**
     * @brief TODO
     */
    operator GLint() const;

private:
    GLuint m_program;
    std::unordered_map<const char*, GLint> m_uniforms;
};

/**
 * @brief TODO
 */
class Material {
public:
    std::shared_ptr<ShaderProgram> m_shader;

    /**
     * @brief TODO
     */
    Material(const std::shared_ptr<ShaderProgram>& shader);

    /**
     * @brief TODO
     */
    virtual ~Material() = default;

    /**
     * @brief TODO
     */
    virtual void bindUniforms(double time, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
};
