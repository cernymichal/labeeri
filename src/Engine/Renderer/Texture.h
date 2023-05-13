#pragma once

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Texture {
public:
    /**
     * @brief TODO
     */
    explicit Texture(LAB_GL_HANDLE texture) : m_texture(texture) {
    }

    Texture(const Texture&) = delete;

    /**
     * @brief TODO
     */
    Texture(Texture&& other) noexcept : m_texture(other.m_texture) {
        other.m_texture = 0;
    }

    /**
     * @brief TODO
     */
    ~Texture();

    operator LAB_GL_HANDLE() const {
        return m_texture;
    }

private:
    LAB_GL_HANDLE m_texture;
};

}  // namespace labeeri::Engine
