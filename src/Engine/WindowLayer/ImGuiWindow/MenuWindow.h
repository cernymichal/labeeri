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

    virtual const std::string& name() const override {
        return m_name;
    }

    virtual bool draw() override;

private:
    const std::string m_name = "Menu";
    bool m_VSync;
};

}  // namespace labeeri::Engine
