#pragma once

#include "Engine/Events/KeyboardEvent.h"
#include "Engine/Events/SceneEvent.h"
#include "Engine/WindowLayer/IWindowLayer.h"
#include "Engine/WindowLayer/ImGuiWindow/IImGuiWindow.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class ImGuiLayer : public IWindowLayer {
public:
    /**
     * @brief TODO
     */
    ImGuiLayer();

    /**
     * @brief TODO
     */
    virtual ~ImGuiLayer() override;

    /**
     * @brief TODO
     */
    IImGuiWindow* addWindow(std::unique_ptr<IImGuiWindow>&& window);

    /**
     * @brief TODO
     */
    virtual void onEvent(IEvent& e) override;

private:
    std::vector<std::unique_ptr<IImGuiWindow>> m_windows;

    void setupImGui();

    bool onRender(const IEvent& e);

    bool onKeyboardPress(const KeyboardPressEvent& e);

    bool onEntityClick(const EntityClickEvent& e);
};

}  // namespace labeeri::Engine
