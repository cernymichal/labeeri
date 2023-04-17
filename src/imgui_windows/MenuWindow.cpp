#include "MenuWindow.h"

#include <imgui.h>

#include "../Application.h"

MenuWindow::MenuWindow(Application& application) : Renderable(application) {
}

void MenuWindow::render() {
    ImGui::Begin("Menu");

    auto framerate = ImGui::GetIO().Framerate;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / framerate, framerate);

    ImGui::End();
}
