#include "MenuWindow.h"

#include <imgui.h>

#include "../Application.h"

MenuWindow::MenuWindow(Application& application) : Renderable(application) {
    glfwSwapInterval(m_VSync ? 1 : 0);
}

void MenuWindow::render() {
    ImGui::Begin("Menu");

    bool vSyncChanged = ImGui::Checkbox("VSync", &m_VSync);
    if (vSyncChanged)
        glfwSwapInterval(m_VSync ? 1 : 0);

    ImGui::Separator();

    auto framerate = ImGui::GetIO().Framerate;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / framerate, framerate);

    ImGui::End();
}
