#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <list>
#include <memory>
#include <utility>

#include "Renderable.h"

// GL 4.3 + GLSL 430
inline const int GL_VERSION_MAJOR = 4;
inline const int GL_VERSION_MINOR = 3;
inline const char* const GLSL_VERSION = "#version 430";

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
    GLFWwindow* window() const;

    /**
     * @brief TODO
     */
    std::pair<int, int> frameBufferSize() const;

private:
    GLFWwindow* m_window = nullptr;
    std::list<std::unique_ptr<Renderable>> m_imguiWindows;
    std::unique_ptr<Renderable> m_viewport;

    /**
     * @brief TODO
     */
    void setupGLFW();

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
    void cleanup();
};
