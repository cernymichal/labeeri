#pragma once

#include "Engine/Scene/Scene.h"
#include "Engine/WindowLayer/IWindowLayer.h"
#include "Engine/WindowLayer/SceneLayer.h"
#include "Engine/WindowLayer/ViewportLayer.h"

struct GLFWwindow;

namespace labeeri::Engine {

enum class ApplicationFocus : uint8_t {
    UI,
    Viewport
};

/**
 * @brief TODO
 */
class Application {
public:
    /**
     * @brief TODO
     */
    static inline Application& get() {
        static Application instance;
        return instance;
    }

    Application(const Application&) = delete;

    Application& operator=(const Application&) = delete;

    /**
     * @brief TODO
     */
    void initialize();

    /**
     * @brief TODO
     */
    void run();

    /**
     * @brief TODO
     */
    inline GLFWwindow* window() const {
        return m_window;
    }

    /**
     * @brief TODO
     */
    glm::uvec2 frameBufferSize() const;

    /**
     * @brief TODO
     */
    static void setVSync(bool enabled);

    /**
     * @brief TODO
     */
    inline std::shared_ptr<Camera>& camera() const {
        return m_viewportLayer->m_camera;
    }

    /**
     * @brief TODO
     */
    inline std::shared_ptr<Scene>& scene() const {
        return m_sceneLayer->m_scene;
    }

    /**
     * @brief TODO
     */
    inline ApplicationFocus focus() const {
        return m_focus;
    }

    /**
     * @brief TODO
     */
    void focusUI();

    /**
     * @brief TODO
     */
    void focusViewport();

    /**
     * @brief TODO
     */
    inline bool closed() const {
        return m_closed;
    }

private:
    bool m_closed = false;
    ApplicationFocus m_focus = ApplicationFocus::UI;
    GLFWwindow* m_window = nullptr;
    std::list<std::unique_ptr<IWindowLayer>> m_layers;
    ViewportLayer* m_viewportLayer;
    SceneLayer* m_sceneLayer;
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
    void emitEvent(Event& e);

    /**
     * @brief TODO
     */
    void emitEvent(ApplicationRenderEvent& e);

    /**
     * @brief TODO
     */
    static void glfwErrorCallback(int error, const char* description);

    /**
     * @brief TODO
     */
    static void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);

    /**
     * @brief TODO
     */
    static void glfwKeyboardCallback(GLFWwindow* window, int keyInt, int scanCode, int actionInt, int mods);

    /**
     * @brief TODO
     */
    static void glfwCursorPosCallback(GLFWwindow* window, double x, double y);

    /**
     * @brief TODO
     */
    static void glfwMouseButtonCallback(GLFWwindow* window, int buttonInt, int actionInt, int mods);

    /**
     * @brief TODO
     */
    static void glfwScrollCallback(GLFWwindow* window, double deltaX, double deltaY);
};

}  // namespace labeeri::Engine
