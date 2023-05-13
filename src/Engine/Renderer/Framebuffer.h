#pragma once

#include "Engine/Renderer/Texture.h"

namespace labeeri::Engine {

enum class FramebufferAttachment {
    Color,
    Depth,
    Stencil,
    DepthStencil
};

/**
 * @brief TODO
 */
class Framebuffer {
public:
    std::map<FramebufferAttachment, Ref<Texture>> m_attachments;

    /**
     * @brief TODO
     */
    Framebuffer(LAB_GL_HANDLE framebufferObject, const std::map<FramebufferAttachment, Ref<Texture>>& attachments)
        : m_framebufferObject(framebufferObject), m_attachments(attachments) {
    }

    Framebuffer(const Texture&) = delete;

    /**
     * @brief TODO
     */
    Framebuffer(Framebuffer&& other) noexcept {
        m_framebufferObject = other.m_framebufferObject;
        m_attachments = std::move(other.m_attachments);
        other.m_framebufferObject = 0;
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
