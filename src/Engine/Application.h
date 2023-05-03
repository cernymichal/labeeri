#pragma once

#include "Engine/Scene/Scene.h"
#include "Engine/WindowLayer/IWindowLayer.h"
#include "Engine/WindowLayer/ImGuiLayer.h"
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
    void emitEvent(IEvent& e);

    /**
     * @brief TODO
     */
    void emitEvent(ApplicationRenderEvent& e);

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

    inline ImGuiLayer* imGuiLayer() const {
        return m_imGuiLayer;
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
    std::list<std::unique_ptr<IWindowLayer>> m_layers;
    ImGuiLayer* m_imGuiLayer = nullptr;
    ViewportLayer* m_viewportLayer = nullptr;
    SceneLayer* m_sceneLayer = nullptr;

    /**
     * @brief TODO
     */
    Application();

    ~Application();
};

}  // namespace labeeri::Engine
