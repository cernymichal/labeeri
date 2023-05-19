#pragma once

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class ShaderResource {
public:
    /**
     * @brief TODO
     */
    explicit ShaderResource(LAB_GL_HANDLE program) : m_program(program) {
    }

    ShaderResource(const ShaderResource&) = delete;

    /**
     * @brief TODO
     */
    ShaderResource(ShaderResource&& other) noexcept : m_program(other.m_program), m_uniforms(std::move(other.m_uniforms)) {
        other.m_program = 0;
    }

    ShaderResource& operator=(const ShaderResource&) = delete;

    ShaderResource& operator=(ShaderResource&& other) noexcept {
        if (this == &other)
            return *this;

        this->~ShaderResource();
        new (this) ShaderResource(std::move(other));
        return *this;
    }

    /**
     * @brief TODO
     */
    ~ShaderResource();

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
