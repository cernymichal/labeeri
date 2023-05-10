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
    explicit Texture(LAB_GL_HANDLE texture);

    Texture(const Texture&) = delete;

    /**
     * @brief TODO
     */
    Texture(Texture&& other) noexcept;

    /**
     * @brief TODO
     */
    ~Texture();

    operator LAB_GL_HANDLE() const;

private:
    LAB_GL_HANDLE m_texture;
};

}  // namespace labeeri::Engine
