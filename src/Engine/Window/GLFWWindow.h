#pragma once

#include "Engine/Window/IWindow.h"

struct GLFWwindow;

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class GLFWWindow : public IWindow {
public:
    /**
     * @brief TODO
     */
    GLFWWindow();

    virtual ~GLFWWindow() override;

    /**
     * @brief TODO
     */
    GLFWwindow* windowObject() const {
        return m_window;
    }

    virtual double currentTime() const override;

    virtual uvec2 m_frameBufferSize() const override {
        return s_frameBufferSize;
    }

    virtual bool VSync() const override {
        return m_VSync;
    }

    virtual void setVSync(bool enabled) override;

    virtual bool fullscreen() const override {
        return m_fullscreen;
    }

    virtual void setFullscreen(bool enabled) override;

    virtual bool minimized() const override {
        return s_minimized || s_frameBufferSize == ivec2(0);
    }

    virtual bool shouldClose() const override;

    virtual void swapBuffers() override;

    virtual void pollEvents() override;

    virtual void setCursorMode(CursorMode mode) override;

    virtual void setClipboardContent(const char* content) const override;

    virtual void* procAddressGetter() const override;

    virtual void makeCurrent() override;

private:
    GLFWwindow* m_window = nullptr;
    bool m_VSync = true;
    bool m_fullscreen = false;
    ivec2 m_windowedPosition = ivec2(0);
    ivec2 m_windowedSize = ivec2(0);

    static inline ivec2 s_frameBufferSize = ivec2(0);
    static inline bool s_minimized = false;
    static inline dvec2 s_mousePosition = dvec2(0);

    void setupGLFW();

    static void GLFWErrorCallback(int error, const char* description);

    static void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height);

    static void GLFWWindowIconifyCallback(GLFWwindow* window, int iconified);

    static void GLFWKeyboardCallback(GLFWwindow* window, int keyInt, int scanCode, int actionInt, int mods);

    static void GLFWCursorPosCallback(GLFWwindow* window, double x, double y);

    static void GLFWMouseButtonCallback(GLFWwindow* window, int buttonInt, int actionInt, int mods);

    static void GLFWScrollCallback(GLFWwindow* window, double deltaX, double deltaY);
};

}  // namespace labeeri::Engine
