#pragma once

#include "WindowLayer/ImGuiWindow/IImGuiWindow.h"

namespace labeeri {

/**
 * @brief ImGui window for displaying help information.
 */
class HelpWindow : public IImGuiWindow {
public:
    virtual const std::string& name() const override {
        return m_name;
    }

    virtual bool draw() override;

private:
    const std::string m_name = "Help";
};

}  // namespace labeeri
