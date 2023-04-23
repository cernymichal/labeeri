#pragma once

using LAB_GL_UINT = unsigned int;  // so that we dont have to include glew everywhere
using LAB_GL_INT = int;
using LAB_GL_HANDLE = LAB_GL_UINT;

namespace labeeri::engine {

/**
 * @brief TODO
 */
class ShaderProgram {
public:
    /**
     * @brief TODO
     */
    ShaderProgram(LAB_GL_HANDLE program);

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
    LAB_GL_INT getUniformLocation(const char* name);

    /**
     * @brief TODO
     */
    operator LAB_GL_HANDLE() const;

private:
    LAB_GL_HANDLE m_program;
    std::unordered_map<const char*, LAB_GL_HANDLE> m_uniforms;
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

}  // namespace labeeri::engine
