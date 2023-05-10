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

    virtual glm::uvec2 frameBufferSize() const override;

    virtual bool VSync() const override {
        return m_VSync;
    }

    virtual void setVSync(bool enabled) override;

    virtual bool fullscreen() const override {
        return m_fullscreen;
    }

    virtual void setFullscreen(bool enabled) override;

    virtual bool minimized() const override;

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
    glm::ivec2 m_windowedPosition = glm::ivec2(0);
    glm::ivec2 m_windowedSize = glm::ivec2(0);
    static glm::dvec2 s_mousePosition;

    void setupGLFW();

    static void glfwErrorCallback(int error, const char* description);

    static void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);

    static void glfwWindowIconifyCallback(GLFWwindow* window, int iconified);

    static void glfwKeyboardCallback(GLFWwindow* window, int keyInt, int scanCode, int actionInt, int mods);

    static void glfwCursorPosCallback(GLFWwindow* window, double x, double y);

    static void glfwMouseButtonCallback(GLFWwindow* window, int buttonInt, int actionInt, int mods);

    static void glfwScrollCallback(GLFWwindow* window, double deltaX, double deltaY);
};

}  // namespace labeeri::Engine
