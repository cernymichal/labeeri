#include "GLFWWindow.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "WindowLayer/ImGuiLayer.h"

namespace labeeri {

GLFWWindow::GLFWWindow() {
    setupGLFW();

    glfwGetFramebufferSize(m_window, &s_frameBufferSize.x, &s_frameBufferSize.y);
    glfwGetWindowContentScale(m_window, &s_contentScale.x, &s_contentScale.y);
    s_minimized = glfwGetWindowAttrib(m_window, GLFW_ICONIFIED);
    glfwGetCursorPos(m_window, &s_mousePosition.x, &s_mousePosition.y);
    GLFWWindow::setVSync(true);
}

GLFWWindow::~GLFWWindow() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

f64 GLFWWindow::currentTime() const {
    return glfwGetTime();
}

void GLFWWindow::setVSync(bool enabled) {
    m_VSync = enabled;
    glfwSwapInterval(m_VSync ? 1 : 0);
}

void GLFWWindow::setFullscreen(bool enabled) {
    if (m_fullscreen == enabled)
        return;

    m_fullscreen = enabled;

    if (!m_fullscreen) {
        glfwSetWindowMonitor(m_window, nullptr, m_windowedPosition.x, m_windowedPosition.y, m_windowedSize.x, m_windowedSize.y, 0);
        return;
    }

    // backup window position and size
    glfwGetWindowPos(m_window, &m_windowedPosition.x, &m_windowedPosition.y);
    glfwGetWindowSize(m_window, &m_windowedSize.x, &m_windowedSize.y);

    // find current monitor
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    i32 monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
    for (i32 i = 0; i < monitorCount; i++) {
        ivec2 monitorPosition;
        glfwGetMonitorPos(monitors[i], &monitorPosition.x, &monitorPosition.y);

        const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);
        ivec2 monitorSize = ivec2(mode->width, mode->height);

        if (glm::all(m_windowedPosition - monitorPosition < monitorSize)) {
            monitor = monitors[i];
            break;
        }
    }

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
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
    i32 glfwMode = GLFW_CURSOR_NORMAL;
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

    glfwSetErrorCallback(GLFWErrorCallback);

    // Initialize the library
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");

    // GL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, LAB_GL_VERSION.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, LAB_GL_VERSION.minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    LAB_DEBUG_ONLY(glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE));

    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    // Create window with graphics context
    m_window = glfwCreateWindow(INITIAL_WINDOW_SIZE.x, INITIAL_WINDOW_SIZE.y, "labeeri", nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("glfwCreateWindow failed");
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback(m_window, GLFWFramebufferSizeCallback);
    glfwSetWindowContentScaleCallback(m_window, GLFWWindowContentScaleCallback);
    glfwSetWindowIconifyCallback(m_window, GLFWWindowIconifyCallback);
    glfwSetKeyCallback(m_window, GLFWKeyboardCallback);
    glfwSetCursorPosCallback(m_window, GLFWCursorPosCallback);
    glfwSetMouseButtonCallback(m_window, GLFWMouseButtonCallback);
    glfwSetScrollCallback(m_window, GLFWScrollCallback);
}

void GLFWWindow::GLFWErrorCallback(i32 error, const char* description) {
    LAB_LOG("GLFW Error " << error << ": " << description);
}

void GLFWWindow::GLFWFramebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
    s_frameBufferSize = uvec2(width, height);

    if (LAB_WINDOW->minimized())
        return;

    WindowResizeEvent resizeEvent(s_frameBufferSize, s_contentScale);
    LAB_APP.emitEvent(resizeEvent);

    // rerender
    ApplicationRenderEvent renderEvent;
    LAB_APP.emitEvent(renderEvent);
}

void GLFWWindow::GLFWWindowContentScaleCallback(GLFWwindow* window, f32 xScale, f32 yScale) {
    s_contentScale = vec2(xScale, yScale);

    if (LAB_WINDOW->minimized())
        return;

    WindowResizeEvent resizeEvent(s_frameBufferSize, s_contentScale);
    LAB_APP.emitEvent(resizeEvent);
}

void GLFWWindow::GLFWWindowIconifyCallback(GLFWwindow* window, i32 iconified) {
    s_minimized = iconified;

    WindowMinimizeEvent event(iconified);
    LAB_APP.emitEvent(event);
}

void GLFWWindow::GLFWKeyboardCallback(GLFWwindow* window, i32 keyInt, i32 scanCode, i32 actionInt, i32 mods) {
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

void GLFWWindow::GLFWCursorPosCallback(GLFWwindow* window, f64 x, f64 y) {
    dvec2 newPosition(x, y);
    dvec2 delta = newPosition - s_mousePosition;
    s_mousePosition = newPosition;

    MouseMoveEvent event(newPosition, delta);
    LAB_APP.emitEvent(event);
}

void GLFWWindow::GLFWMouseButtonCallback(GLFWwindow* window, i32 buttonInt, i32 actionInt, i32 mods) {
    auto button = static_cast<MouseButton>(buttonInt);
    auto action = static_cast<KeyAction>(actionInt);

    if (action == KeyAction::Repeat)
        return;

    dvec2 position;
    glfwGetCursorPos(window, &position.x, &position.y);

    switch (action) {
        case KeyAction::Press: {
            MouseButtonPressEvent event(button, mods, position);
            LAB_APP.emitEvent(event);
            break;
        }
        case KeyAction::Release: {
            MouseButtonReleaseEvent event(button, mods, position);
            LAB_APP.emitEvent(event);
            break;
        }
        case KeyAction::Repeat:
            break;
    }
}

void GLFWWindow::GLFWScrollCallback(GLFWwindow* window, f64 deltaX, f64 deltaY) {
    MouseScrollEvent event(deltaY);
    LAB_APP.emitEvent(event);
}

}  // namespace labeeri
