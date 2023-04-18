#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>

/**
 * @brief TODO
 */
class Shader {
public:
    const GLuint m_program;

    /**
     * @brief TODO
     */
    Shader(GLuint program);

    /**
     * @brief TODO
     */
    ~Shader();

    /**
     * @brief TODO
     */
    GLint getUniformLocation(const char* name);

private:
    std::unordered_map<const char*, GLint> m_uniforms;
};

/**
 * @brief TODO
 */
class Material {
public:
    std::shared_ptr<Shader> m_shader;

    /**
     * @brief TODO
     */
    Material(const std::shared_ptr<Shader>& shader);

    /**
     * @brief TODO
     */
    virtual ~Material() = default;

    /**
     * @brief TODO
     */
    virtual void bindUniforms(double time, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
};
