#include "MenuWindow.h"

#include <imgui.h>

#include "Engine/Application.h"
#include "Engine/Window/IWindow.h"
#include "Engine/WindowLayer/ImGuiWindow/LogWindow.h"

namespace labeeri::Engine {

MenuWindow::MenuWindow() {
    m_VSync = LAB_WINDOW->VSync();
}

bool MenuWindow::draw() {
    ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);

    ImGui::Begin(m_name.c_str());

    bool vSyncChanged = ImGui::Checkbox("VSync", &m_VSync);
    if (vSyncChanged)
        LAB_WINDOW->setVSync(m_VSync);

    if (ImGui::Button("Open Log"))
        LAB_IMGUI->addWindow(std::make_unique<LogWindow>());

    ImGui::Separator();

    auto framerate = ImGui::GetIO().Framerate;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / framerate, framerate);

    ImGui::End();

    return true;
}

}  // namespace labeeri::Engine
