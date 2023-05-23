#pragma once

namespace labeeri::Engine {

/**
 * @brief A shared texture resource.
 */
class TextureResource {
public:
    /**
     * @param texture The OpenGL handle to the texture.
     */
    explicit TextureResource(LAB_GL_HANDLE texture) : m_texture(texture) {
    }

    TextureResource(const TextureResource&) = delete;

    /**
     * @param other The texture resource to move.
     */
    TextureResource(TextureResource&& other) noexcept : m_texture(other.m_texture) {
        other.m_texture = 0;
    }

    TextureResource& operator=(const TextureResource&) = delete;

    /**
     * @param other The texture resource to move.
     */
    TextureResource& operator=(TextureResource&& other) noexcept {
        if (this == &other)
            return *this;

        this->~TextureResource();
        new (this) TextureResource(std::move(other));
        return *this;
    }

    /**
     * @brief Destroys the texture resource.
     *
     * Calls deleteTexture on the renderer.
     */
    ~TextureResource();

    /**
     * @brief The texture handle.
     */
    operator LAB_GL_HANDLE() const {
        return m_texture;
    }

private:
    LAB_GL_HANDLE m_texture;
};

}  // namespace labeeri::Engine
