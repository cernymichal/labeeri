#pragma once

#include "Engine/WindowLayer/ImGuiWindow/IImGuiWindow.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class MenuWindow : public IImGuiWindow {
public:
    /**
     * @brief TODO
     */
    MenuWindow();

    /**
     * @brief TODO
     */
    virtual void draw() override;

private:
    bool m_VSync;
};

}  // namespace labeeri::Engine
