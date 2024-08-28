#pragma once

#include "WindowLayer/ImGuiWindow/IImGuiWindow.h"

namespace labeeri {

/**
 * @brief ImGui window for editing basic renderer settings and displaying other windows.
 */
class MenuWindow : public IImGuiWindow {
public:
    MenuWindow();

    virtual const std::string& name() const override {
        return m_name;
    }

    virtual bool draw() override;

private:
    const std::string m_name = "Menu";
    bool m_VSync;
};

}  // namespace labeeri
