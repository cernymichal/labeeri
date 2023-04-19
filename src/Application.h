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

// GL 4.3 + GLSL 430
constexpr auto GL_VERSION_MAJOR = 4;
constexpr auto GL_VERSION_MINOR = 3;
constexpr auto GLSL_VERSION = "#version 430";

/**
 * @brief TODO
 */
class Application {
public:
    /**
     * @brief TODO
     */
    Application();

    /**
     * @brief TODO
     */
    void start();

    /**
     * @brief TODO
     */
    Scene& scene() const;

    /**
     * @brief TODO
     */
    GLFWwindow* window() const;

    /**
     * @brief TODO
     */
    std::pair<int, int> frameBufferSize() const;

private:
    std::unique_ptr<Scene> m_scene;

    GLFWwindow* m_window = nullptr;
    std::list<std::unique_ptr<Renderable>> m_imguiWindows;
    std::unique_ptr<Viewport> m_viewport;

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
    void mainLoop();

    /**
     * @brief TODO
     */
    void render();

    /**
     * @brief TODO
     */
    void cleanup();
};
