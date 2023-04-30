#pragma once

namespace labeeri::Engine {

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

using ShaderProgramRef = std::shared_ptr<ShaderProgram>;

}  // namespace labeeri::Engine
