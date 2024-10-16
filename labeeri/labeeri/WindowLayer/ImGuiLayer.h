#pragma once

#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/SceneEvent.h"
#include "WindowLayer/IWindowLayer.h"
#include "WindowLayer/ImGuiWindow/IImGuiWindow.h"

namespace labeeri {

/**
 * @brief Handles all ImGui windows.
 */
class ImGuiLayer : public IWindowLayer {
public:
    /**
     * @brief Initializes ImGui.
     */
    ImGuiLayer();

    /**
     * @brief Disposes of the ImGui context.
     */
    virtual ~ImGuiLayer() override;

    /**
     * @brief Adds a window to the layer if it is not already added.
     *
     * @param window The window to add.
     * @return IImGuiWindow* The window that was added.
     */
    IImGuiWindow* addWindow(std::unique_ptr<IImGuiWindow>&& window);

    virtual void onEvent(IEvent& e) override;

private:
    std::vector<std::unique_ptr<IImGuiWindow>> m_windows;

    void setupImGui();

    bool onRender(const ApplicationRenderEvent& e);

    bool onWindowResize(const WindowResizeEvent& e);

    bool onKeyboardPress(const KeyboardPressEvent& e);

    bool onEntityClick(const EntityClickEvent& e);
};

}  // namespace labeeri
