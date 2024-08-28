#pragma once

#include "Scene/Scene.h"
#include "WindowLayer/IWindowLayer.h"
#include "WindowLayer/ImGuiLayer.h"
#include "WindowLayer/SceneLayer.h"
#include "WindowLayer/ViewportLayer.h"

struct GLFWwindow;

namespace labeeri {

enum class ApplicationFocus : u8 {
    UI,
    Viewport
};

/**
 * @brief Singleton class that manages the event system and window layers.
 */
class Application {
public:
    /**
     * @brief Get a reference to the singleton instance, creates one if it doesn't exist.
     *
     * @return A reference to the singleton instance.
     */
    static Application& Instance() {
        static Application instance;
        return instance;
    }

    Application(const Application&) = delete;

    Application& operator=(const Application&) = delete;

    /**
     * @brief Creates all the window layers. Needs to be called!
     */
    void initialize();

    /**
     * @brief Enter the main loop. Queries window events and calls the window layers.
     */
    void run();

    /**
     * @brief Creates and propagates a new event through the window layers.
     *
     * @param e The event to be emitted.
     */
    void emitEvent(IEvent& e) const;

    /**
     * @brief Renders the window layers back to front and swaps the buffers.
     *
     * @param e The event to be emitted.
     */
    void emitEvent(ApplicationRenderEvent& e);

    /**
     * @return A reference to the viewport camera entity.
     */
    Entity& camera() const {
        return m_viewportLayer->m_camera;
    }

    /**
     * @return The current scene.
     */
    const Ref<Scene>& scene() const {
        return m_sceneLayer->scene();
    }

    /**
     * @brief Sets a new scene. Needs to be called so that the ECS system can be updated.
     *
     * @param scene The new scene.
     */
    void setScene(const Ref<Scene>& scene) const {
        return m_sceneLayer->setScene(scene);
    }

    /**
     * @return The application's ImGuiLayer.
     */
    ImGuiLayer* imGuiLayer() const {
        return m_imGuiLayer;
    }

    /**
     * @return The application's focus state.
     */
    ApplicationFocus focus() const {
        return m_focus;
    }

    /**
     * @brief Focuses the UI overlay.
     */
    void focusUI();

    /**
     * @brief Focuses the viewport.
     */
    void focusViewport();

    /**
     * @return If the application was closed.
     */
    bool closed() const {
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
     * @brief Construct a new Application object. The rendrerer and window abstractions are initialized here.
     */
    Application();

    ~Application();
};

}  // namespace labeeri
