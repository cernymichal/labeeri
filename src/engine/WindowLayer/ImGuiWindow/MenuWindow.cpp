#include "MenuWindow.h"

#include <imgui.h>

#include "Engine/Application.h"

namespace labeeri::Engine {

MenuWindow::MenuWindow() {
    Application::setVSync(m_VSync);
}

void MenuWindow::draw() {
    ImGui::Begin("Menu");

    bool vSyncChanged = ImGui::Checkbox("VSync", &m_VSync);
    if (vSyncChanged)
        Application::setVSync(m_VSync);

    bool throwException = ImGui::Button("Exception");

    ImGui::Separator();

    auto framerate = ImGui::GetIO().Framerate;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / framerate, framerate);

    ImGui::End();

    if (throwException)
        throw std::runtime_error("Exception thrown from MenuWindow");
}

}  // namespace labeeri::Engine
