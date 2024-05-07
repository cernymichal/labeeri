#pragma once

#include "Engine/Window/IWindow.h"

struct GLFWwindow;

namespace labeeri::Engine {

/**
 * @brief GLFW window abstraction.
 */
class GLFWWindow : public IWindow {
public:
    /**
     * @brief Initializes the GLFW window.
     */
    GLFWWindow();

    virtual ~GLFWWindow() override;

    /**
     * @return The GLFW window object.
     */
    GLFWwindow* windowObject() const {
        return m_window;
    }

    virtual f64 currentTime() const override;

    virtual uvec2 frameSize() const override {
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

    static void GLFWErrorCallback(i32 error, const char* description);

    static void GLFWFramebufferSizeCallback(GLFWwindow* window, i32 width, i32 height);

    static void GLFWWindowIconifyCallback(GLFWwindow* window, i32 iconified);

    static void GLFWKeyboardCallback(GLFWwindow* window, i32 keyInt, i32 scanCode, i32 actionInt, i32 mods);

    static void GLFWCursorPosCallback(GLFWwindow* window, f64 x, f64 y);

    static void GLFWMouseButtonCallback(GLFWwindow* window, i32 buttonInt, i32 actionInt, i32 mods);

    static void GLFWScrollCallback(GLFWwindow* window, f64 deltaX, f64 deltaY);
};

}  // namespace labeeri::Engine
