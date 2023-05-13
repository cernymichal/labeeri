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
    explicit ShaderProgram(LAB_GL_HANDLE program) : m_program(program) {
    }

    ShaderProgram(const ShaderProgram&) = delete;

    /**
     * @brief TODO
     */
    ShaderProgram(ShaderProgram&& other) noexcept : m_program(other.m_program) {
        other.m_program = 0;
    }

    /**
     * @brief TODO
     */
    ~ShaderProgram();

    /**
     * @brief TODO
     */
    LAB_GL_INT getUniformLocation(const std::string& name);

    /**
     * @brief TODO
     */
    operator LAB_GL_HANDLE() const {
        return m_program;
    }

private:
    LAB_GL_HANDLE m_program;
    std::unordered_map<std::string, LAB_GL_INT> m_uniforms;
};

}  // namespace labeeri::Engine
