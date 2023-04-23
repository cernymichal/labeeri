#pragma once

#include "IRenderable.h"
#include "Viewport.h"
#include "scene/Scene.h"

#define LAB_APP labeeri::engine::Application::get()
#define LAB_CURRENT_SCENE LAB_APP.m_scene
#define LAB_CURRENT_CAMERA LAB_APP.camera()

struct GLFWwindow;

namespace labeeri::engine {

// GL 4.3 + GLSL 430
constexpr auto GL_VERSION_MAJOR = 4;
constexpr auto GL_VERSION_MINOR = 3;
constexpr auto GLSL_VERSION = "#version 430";

/**
 * @brief TODO
 */
class Application {
public:
    std::shared_ptr<Scene> m_scene;

    /**
     * @brief TODO
     */
    static Application& get();

    Application(const Application&) = delete;

    Application& operator=(const Application&) = delete;

    /**
     * @brief TODO
     */
    void run();

    /**
     * @brief TODO
     */
    std::shared_ptr<Camera>& camera() const;

    /**
     * @brief TODO
     */
    GLFWwindow* window() const;

    /**
     * @brief TODO
     */
    std::pair<int, int> frameBufferSize() const;

    /**
     * @brief TODO
     */
    void setVSync(bool enabled);

    /**
     * @brief TODO
     */
    bool closed() const;

private:
    bool m_closed = false;
    GLFWwindow* m_window = nullptr;
    std::list<std::unique_ptr<IRenderable>> m_imguiWindows;
    std::unique_ptr<Viewport> m_viewport;

    glm::dvec2 m_mousePosition;

    /**
     * @brief TODO
     */
    Application();

    /**
     * @brief TODO
     */
    ~Application();

    /**
     * @brief TODO
     */
    void setupGLFW();

    /**
     * @brief TODO
     */
    void setupGL();

    /**
     * @brief TODO
     */
    void setupImGui();

    /**
     * @brief TODO
     */
    void render();

    /**
     * @brief TODO
     */
    static void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);

    /**
     * @brief TODO
     */
    static void glfwKeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

    /**
     * @brief TODO
     */
    static void glfwCursorPosCallback(GLFWwindow* window, double x, double y);

    /**
     * @brief TODO
     */
    static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    /**
     * @brief TODO
     */
    static void glfwScrollCallback(GLFWwindow* window, double deltaX, double deltaY);
};

}  // namespace labeeri::engine
