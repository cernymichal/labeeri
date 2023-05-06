#pragma once

#include "Engine/WindowLayer/ImGuiWindow/IImGuiWindow.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class LogWindow : public IImGuiWindow {
public:
    /**
     * @brief TODO
     */
    virtual void draw() override;

private:
    bool m_autoScroll = true;
};

}  // namespace labeeri::Engine
