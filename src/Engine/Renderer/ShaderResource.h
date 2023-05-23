#pragma once

namespace labeeri::Engine {

/**
 * @brief A shadered shader resource.
 */
class ShaderResource {
public:
    /**
     * @param program The OpenGL handle to the shader program.
     */
    explicit ShaderResource(LAB_GL_HANDLE program) : m_program(program) {
    }

    ShaderResource(const ShaderResource&) = delete;

    /**
     * @param other The shader resource to move.
     */
    ShaderResource(ShaderResource&& other) noexcept : m_program(other.m_program), m_uniforms(std::move(other.m_uniforms)) {
        other.m_program = 0;
    }

    ShaderResource& operator=(const ShaderResource&) = delete;

    /**
     * @param other The shader resource to move.
     */
    ShaderResource& operator=(ShaderResource&& other) noexcept {
        if (this == &other)
            return *this;

        this->~ShaderResource();
        new (this) ShaderResource(std::move(other));
        return *this;
    }

    /**
     * @brief Destroy the shader resource. Calls deleteShader on the renderer.
     */
    ~ShaderResource();

    /**
     * @brief Get the location of a uniform in the shader.
     *
     * @param name The name of the uniform.
     * @return The location of the uniform.
     */
    LAB_GL_INT getUniformLocation(const std::string& name);

    /**
     * @brief The shader program handle.
     */
    operator LAB_GL_HANDLE() const {
        return m_program;
    }

private:
    LAB_GL_HANDLE m_program;
    std::unordered_map<std::string, LAB_GL_INT> m_uniforms;
};

}  // namespace labeeri::Engine
