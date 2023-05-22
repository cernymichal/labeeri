#include "HelpWindow.h"

#include <imgui.h>

namespace labeeri::Engine {

bool HelpWindow::draw() {
    ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);

    bool shouldContinue = true;
    ImGui::Begin(m_name.c_str(), &shouldContinue);

    ImGui::Text("Click into the scene or use ESC to return back to UI");
    ImGui::Text("Use the WASD keys to move, sprint with left shift");
    ImGui::Text("Left click to interact with objects");
    ImGui::Text("F1 switch to flycam / player");
    ImGui::Text("Page up / down go through static cameras");
    ImGui::Text("F3 to show/hide interface");
    ImGui::Text("F5 switches to fullscreen");
    ImGui::Text("Ctrl + left click objects to edit them in UI mode");

    ImGui::End();

    return shouldContinue;
}

}  // namespace labeeri::Engine
