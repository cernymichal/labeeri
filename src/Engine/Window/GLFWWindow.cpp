#include "GLFWWindow.h"

#include <GLFW/glfw3.h>

#include "Engine/Application.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Resources/Resources.h"
#include "Engine/Scene/Entity.h"
#include "Engine/WindowLayer/ImGuiLayer.h"
#include "Engine/WindowLayer/SceneLayer.h"
#include "Engine/WindowLayer/ViewportLayer.h"

namespace labeeri::Engine {

glm::dvec2 GLFWWindow::s_mousePosition = glm::dvec2(0.0);

GLFWWindow::GLFWWindow() {
    setupGLFW();

    glfwGetCursorPos(m_window, &s_mousePosition.x, &s_mousePosition.y);
    setVSync(true);
}

GLFWWindow::~GLFWWindow() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

double GLFWWindow::currentTime() const {
    return glfwGetTime();
}

glm::uvec2 GLFWWindow::frameBufferSize() const {
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    return glm::uvec2(width, height);
}

void GLFWWindow::setVSync(bool enabled) {
    m_VSync = enabled;
    glfwSwapInterval(m_VSync ? 1 : 0);
}

bool GLFWWindow::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void GLFWWindow::swapBuffers() {
    glfwSwapBuffers(m_window);
}

void GLFWWindow::pollEvents() {
    glfwPollEvents();
}

void GLFWWindow::setCursorMode(CursorMode mode) {
    int glfwMode = GLFW_CURSOR_NORMAL;
    switch (mode) {
        case CursorMode::Normal:
            glfwMode = GLFW_CURSOR_NORMAL;
            break;
        case CursorMode::Hidden:
            glfwMode = GLFW_CURSOR_HIDDEN;
            break;
        case CursorMode::Disabled:
            glfwMode = GLFW_CURSOR_DISABLED;
            break;
    }

    glfwSetInputMode(m_window, GLFW_CURSOR, glfwMode);
}

void GLFWWindow::setClipboardContent(const char* content) const {
    glfwSetClipboardString(m_window, content);
}

void* GLFWWindow::procAddressGetter() const {
    return glfwGetProcAddress;
}

void GLFWWindow::makeCurrent() {
    glfwMakeContextCurrent(m_window);
}

void GLFWWindow::setupGLFW() {
    LAB_LOGH3("GLFWWindow::setupGLFW()");

    glfwSetErrorCallback(glfwErrorCallback);

    // Initialize the library
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");

    // GL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // Create window with graphics context
    m_window = glfwCreateWindow(INITIAL_WINDOW_SIZE.x, INITIAL_WINDOW_SIZE.y, "labeeri", NULL, NULL);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("glfwCreateWindow failed");
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback(m_window, glfwFramebufferSizeCallback);
    glfwSetKeyCallback(m_window, glfwKeyboardCallback);
    glfwSetCursorPosCallback(m_window, glfwCursorPosCallback);
    glfwSetMouseButtonCallback(m_window, glfwMouseButtonCallback);
    glfwSetScrollCallback(m_window, glfwScrollCallback);
}

void GLFWWindow::glfwErrorCallback(int error, const char* description) {
    LAB_LOG("GLFW Error " << error << ": " << description);
}

void GLFWWindow::glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    WindowResizeEvent resizeEvent(glm::uvec2(width, height));
    LAB_APP.emitEvent(resizeEvent);

    // rerender
    ApplicationRenderEvent renderEvent;
    LAB_APP.emitEvent(renderEvent);
}

void GLFWWindow::glfwKeyboardCallback(GLFWwindow* window, int keyInt, int scanCode, int actionInt, int mods) {
    auto key = static_cast<KeyboardKey>(keyInt);
    auto action = static_cast<KeyAction>(actionInt);

    switch (action) {
        case KeyAction::Press: {
            KeyboardPressEvent event(key, scanCode, mods);
            LAB_APP.emitEvent(event);
            break;
        }
        case KeyAction::Repeat: {
            KeyboardRepeatEvent event(key, scanCode, mods);
            LAB_APP.emitEvent(event);
            break;
        }
        case KeyAction::Release: {
            KeyboardReleaseEvent event(key, scanCode, mods);
            LAB_APP.emitEvent(event);
            break;
        }
    }
}

void GLFWWindow::glfwCursorPosCallback(GLFWwindow* window, double x, double y) {
    glm::dvec2 newPosition(x, y);
    glm::dvec2 delta = newPosition - s_mousePosition;
    s_mousePosition = newPosition;

    MouseMoveEvent event(newPosition, delta);
    LAB_APP.emitEvent(event);
}

void GLFWWindow::glfwMouseButtonCallback(GLFWwindow* window, int buttonInt, int actionInt, int mods) {
    auto button = static_cast<MouseButton>(buttonInt);
    auto action = static_cast<KeyAction>(actionInt);

    switch (action) {
        case KeyAction::Press: {
            MouseButtonPressEvent event(button, mods);
            LAB_APP.emitEvent(event);
            break;
        }
        case KeyAction::Release: {
            MouseButtonReleaseEvent event(button, mods);
            LAB_APP.emitEvent(event);
            break;
        }
    }
}

void GLFWWindow::glfwScrollCallback(GLFWwindow* window, double deltaX, double deltaY) {
    MouseScrollEvent event(deltaY);
    LAB_APP.emitEvent(event);
}

}  // namespace labeeri::Engine
