#pragma once

#include "Engine/WindowLayer/ImGuiWindow/IImGuiWindow.h"

namespace labeeri::Engine {

/**
 * @brief TODO
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

}  // namespace labeeri::Engine
