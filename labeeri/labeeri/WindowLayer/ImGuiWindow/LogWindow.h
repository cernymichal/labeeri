#pragma once

#include "WindowLayer/ImGuiWindow/IImGuiWindow.h"

namespace labeeri {

/**
 * @brief ImGui window for displaying the log.
 */
class LogWindow : public IImGuiWindow {
public:
    virtual const std::string& name() const override {
        return m_name;
    }

    virtual bool draw() override;

private:
    const std::string m_name = "Log";
    bool m_autoScroll = true;
};

}  // namespace labeeri
