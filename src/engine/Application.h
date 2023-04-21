#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <list>
#include <memory>
#include <utility>

#include "Renderable.h"
#include "Viewport.h"
#include "scene/Scene.h"

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
    Application();

    /**
     * @brief TODO
     */
    ~Application();

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
    bool closed() const;

private:
    GLFWwindow* m_window = nullptr;
    std::list<std::unique_ptr<Renderable>> m_imguiWindows;
    std::unique_ptr<Viewport> m_viewport;
    bool m_closed = false;

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
};

}  // namespace labeeri::engine