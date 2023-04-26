#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Resources/Resources.h"
#include "Engine/Scene/Entity.h"
#include "Engine/WindowLayer/ImGuiLayer.h"
#include "Engine/WindowLayer/SceneLayer.h"
#include "Engine/WindowLayer/ViewportLayer.h"

namespace labeeri::Engine {

Application::Application() {
    LAB_LOGH2("Application::Application()");

    setupGLFW();
    setupGL();
}

Application::~Application() {
    LAB_LOGH2("Application::~Application()");

    m_layers.clear();

    LAB_LOG_OGL_ERROR();

    glfwDestroyWindow(m_window);
    glfwTerminate();

    LAB_DEBUG_ONLY(std::cout << LAB_LOGSTREAM_STR << std::endl);
}

void Application::initialize() {
    LAB_LOGH2("Application::initialize()");

    m_layers.push_back(std::make_unique<ImGuiLayer>());
    m_layers.push_back(std::make_unique<ViewportLayer>());
    m_viewportLayer = dynamic_cast<ViewportLayer*>(m_layers.back().get());
    m_layers.push_back(std::make_unique<SceneLayer>());
    m_sceneLayer = dynamic_cast<SceneLayer*>(m_layers.back().get());
}

glm::uvec2 Application::frameBufferSize() const {
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    return glm::uvec2(width, height);
}

void Application::setVSync(bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
}

void Application::focusUI() {
    if (closed())
        return;

    m_focus = ApplicationFocus::UI;
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Application::focusViewport() {
    if (closed())
        return;

    m_focus = ApplicationFocus::Viewport;
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::setupGLFW() {
    LAB_LOGH2("Application::setupGLFW()");

    glfwSetErrorCallback(glfwErrorCallback);

    // Initialize the library
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");

    // GL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);         // 3.0+ only

    // Create window with graphics context
    m_window = glfwCreateWindow(1600, 1200, "labeeri", NULL, NULL);
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

void Application::setupGL() {
    LAB_LOGH2("Application::setupGL()");

    glewExperimental = GL_TRUE;
    GLenum status = glewInit();
    if (status != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    LAB_LOG("Renderer: " << glGetString(GL_RENDERER));
    LAB_LOG("OpenGL version: " << glGetString(GL_VERSION));
}

void Application::emitEvent(Event& e) {
    for (auto& layer : m_layers) {
        layer->onEvent(e);

        if (e.m_handled)
            break;
    }
}

void Application::emitEvent(ApplicationRenderEvent& e) {
    for (auto& layer : std::ranges::views::reverse(m_layers))
        layer->onEvent(e);
}

void Application::run() {
    LAB_LOGH2("Application::run()");

    double previousUpdateTime = glfwGetTime();
    double fixedUpdateTimeAccumulator = 0;
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - previousUpdateTime;
        previousUpdateTime = currentTime;
        fixedUpdateTimeAccumulator += deltaTime;

        // emit fixed updates
        while (fixedUpdateTimeAccumulator >= FIXED_UPDATE_INTERVAL) {
            ApplicationFixedUpdateEvent fixedUpdateEvent;
            emitEvent(fixedUpdateEvent);

            fixedUpdateTimeAccumulator -= FIXED_UPDATE_INTERVAL;
        }

        // emit update
        ApplicationUpdateEvent updateEvent(deltaTime);
        emitEvent(updateEvent);

        // emit render
        ApplicationRenderEvent renderEvent;
        emitEvent(renderEvent);

        glfwSwapBuffers(m_window);
    }

    m_closed = true;
}

void Application::glfwErrorCallback(int error, const char* description) {
    LAB_LOG("GLFW Error " << error << ": " << description);
}

void Application::glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    WindowResizeEvent resizeEvent(glm::uvec2(width, height));
    LAB_APP.emitEvent(resizeEvent);

    // rerender
    ApplicationRenderEvent renderEvent;
    LAB_APP.emitEvent(renderEvent);
}

void Application::glfwKeyboardCallback(GLFWwindow* window, int keyInt, int scanCode, int actionInt, int mods) {
    auto key = static_cast<Keyboard>(keyInt);
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

void Application::glfwCursorPosCallback(GLFWwindow* window, double x, double y) {
    glm::dvec2 newPosition(x, y);
    glm::dvec2 delta = newPosition - LAB_APP.m_mousePosition;
    LAB_APP.m_mousePosition = newPosition;

    MouseMoveEvent event(newPosition, delta);
    LAB_APP.emitEvent(event);
}

void Application::glfwMouseButtonCallback(GLFWwindow* window, int buttonInt, int actionInt, int mods) {
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

void Application::glfwScrollCallback(GLFWwindow* window, double deltaX, double deltaY) {
    MouseScrollEvent event(deltaY);
    LAB_APP.emitEvent(event);
}

}  // namespace labeeri::Engine
