#pragma once

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class TextureResource {
public:
    /**
     * @brief TODO
     */
    explicit TextureResource(LAB_GL_HANDLE texture) : m_texture(texture) {
    }

    TextureResource(const TextureResource&) = delete;

    /**
     * @brief TODO
     */
    TextureResource(TextureResource&& other) noexcept : m_texture(other.m_texture) {
        other.m_texture = 0;
    }

    TextureResource& operator=(const TextureResource&) = delete;

    TextureResource& operator=(TextureResource&& other) noexcept {
        if (this == &other)
            return *this;

        this->~TextureResource();
        new (this) TextureResource(std::move(other));
        return *this;
    }

    /**
     * @brief TODO
     */
    ~TextureResource();

    operator LAB_GL_HANDLE() const {
        return m_texture;
    }

private:
    LAB_GL_HANDLE m_texture;
};

}  // namespace labeeri::Engine
