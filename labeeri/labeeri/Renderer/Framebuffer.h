#pragma once

#include "Renderer/TextureResource.h"

namespace labeeri {

/**
 * @brief Buffer types of the framebuffer attachments.
 */
enum class FramebufferAttachment {
    Color,
    Depth,
    Stencil
};

/**
 * @brief Describes a framebuffer object in the renderer.
 */
class Framebuffer {
public:
    uvec2 m_size;
    std::map<FramebufferAttachment, Ref<TextureResource>> m_attachments;

    /**
     * @param size The dimensions of the framebuffer.
     * @param attachments The attachments of the framebuffer.
     */
    Framebuffer(LAB_GL_HANDLE framebufferObject, uvec2 size, std::map<FramebufferAttachment, Ref<TextureResource>>&& attachments)
        : m_size(size), m_attachments(attachments), m_framebufferObject(framebufferObject) {
    }

    Framebuffer(const TextureResource&) = delete;

    /**
     * @param other The framebuffer to move.
     */
    Framebuffer(Framebuffer&& other) noexcept
        : m_size(other.m_size), m_attachments(std::move(other.m_attachments)), m_framebufferObject(other.m_framebufferObject) {
        other.m_framebufferObject = 0;
    }

    Framebuffer& operator=(const TextureResource&) = delete;

    /**
     * @param other The framebuffer to move.
     */
    Framebuffer& operator=(Framebuffer&& other) noexcept {
        this->~Framebuffer();
        new (this) Framebuffer(std::move(other));
        return *this;
    }

    /**
     * @brief Destroys the framebuffer.
     *
     * Calls deleteFramebuffer on the renderer.
     */
    ~Framebuffer();

    /**
     * @brief The framebuffer handle.
     */
    operator LAB_GL_HANDLE() const {
        return m_framebufferObject;
    }

private:
    LAB_GL_HANDLE m_framebufferObject;
};

}  // namespace labeeri
