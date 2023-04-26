#pragma once

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
    ~ImGuiLayer();

    /**
     * @brief TODO
     */
    void onEvent(Event& e) override;

private:
    std::list<std::unique_ptr<IImGuiWindow>> m_windows;

    void setupImGui();

    bool onRender(const Event& e);
};

}  // namespace labeeri::Engine
