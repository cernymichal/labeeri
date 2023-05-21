#pragma once

#include "Engine/Renderer/TextureResource.h"

namespace labeeri::Engine {

enum class FramebufferAttachment {
    Color,
    Depth,
    Stencil
};

/**
 * @brief TODO
 */
class Framebuffer {
public:
    uvec2 m_size;
    std::map<FramebufferAttachment, Ref<TextureResource>> m_attachments;

    /**
     * @brief TODO
     */
    Framebuffer(LAB_GL_HANDLE framebufferObject, uvec2 size, std::map<FramebufferAttachment, Ref<TextureResource>>&& attachments)
        : m_size(size), m_attachments(attachments), m_framebufferObject(framebufferObject) {
    }

    Framebuffer(const TextureResource&) = delete;

    /**
     * @brief TODO
     */
    Framebuffer(Framebuffer&& other) noexcept
        : m_size(other.m_size), m_attachments(std::move(other.m_attachments)), m_framebufferObject(other.m_framebufferObject) {
        other.m_framebufferObject = 0;
    }

    Framebuffer& operator=(const TextureResource&) = delete;

    Framebuffer& operator=(Framebuffer&& other) noexcept {
        this->~Framebuffer();
        new (this) Framebuffer(std::move(other));
        return *this;
    }

    /**
     * @brief TODO
     */
    ~Framebuffer();

    operator LAB_GL_HANDLE() const {
        return m_framebufferObject;
    }

private:
    LAB_GL_HANDLE m_framebufferObject;
};

}  // namespace labeeri::Engine
