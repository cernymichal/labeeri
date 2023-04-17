#pragma once

#include <GL/glew.h>

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <unordered_map>

/**
 * @brief TODO
 */
class Mesh {
public:
    const GLuint m_vertexArrayObject;
    const GLuint m_elementBufferObject;
    const uint32_t m_triangleCount;

    /**
     * @brief TODO
     */
    Mesh(GLuint vertexBufferObject, GLuint elementBufferObject, GLuint vertexArrayObject, uint32_t triangleCount)
        : m_elementBufferObject(elementBufferObject), m_vertexArrayObject(vertexArrayObject), m_triangleCount(triangleCount) {
    }

    /**
     * @brief TODO
     */
    ~Mesh() {
        glDeleteBuffers(1, &m_elementBufferObject);
        glDeleteVertexArrays(1, &m_vertexArrayObject);
    }
};

/**
 * @brief TODO
 */
class Shader {
public:
    const GLuint m_program;

    /**
     * @brief TODO
     */
    Shader(GLuint program) : m_program(program) {
    }

    /**
     * @brief TODO
     */
    ~Shader() {
        glDeleteProgram(m_program);
    }

    /**
     * @brief TODO
     */
    GLint getUniformLocation(const char* name) {
        auto iter = m_uniforms.find(name);

        if (iter != m_uniforms.end())
            return (*iter).second;

        GLint location = glGetUniformLocation(m_program, name);
        if (location != -1)
            m_uniforms[name] = location;

        return location;
    }

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
    Material(const std::shared_ptr<Shader>& shader) : m_shader(shader) {
    }

    /**
     * @brief TODO
     */
    virtual ~Material() = default;

    /**
     * @brief TODO
     */
    virtual void bind(float time, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
        glm::mat4 PVM = projectionMatrix * viewMatrix * modelMatrix;

        const glm::mat4 modelRotationMatrix = glm::mat4(
            modelMatrix[0],
            modelMatrix[1],
            modelMatrix[2],
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelRotationMatrix));

        glUniform1f(m_shader->getUniformLocation("time"), time);
        glUniformMatrix4fv(m_shader->getUniformLocation("PVM_matrix"), 1, GL_FALSE, glm::value_ptr(PVM));
        glUniformMatrix4fv(m_shader->getUniformLocation("view_matrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(m_shader->getUniformLocation("model_matrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(m_shader->getUniformLocation("normal_matrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
};
