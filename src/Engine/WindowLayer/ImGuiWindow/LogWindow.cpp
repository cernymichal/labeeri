#include "LogWindow.h"

#include <imgui.h>

#include "Engine/Window/IWindow.h"

namespace labeeri::Engine {

bool LogWindow::draw() {
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

    bool shouldContinue = true;
    ImGui::Begin(m_name.c_str(), &shouldContinue);

    bool autoScrollChanged = ImGui::Checkbox("Auto-scroll", &m_autoScroll);
    ImGui::SameLine(ImGui::GetWindowWidth() - 100);
    if (ImGui::SmallButton("Clear"))
        LOG_STREAM.str("");
    ImGui::SameLine();
    if (ImGui::SmallButton("Copy"))
        LAB_WINDOW->setClipboardContent(LOG_STREAM.str().c_str());

    ImGui::Separator();

    ImGui::BeginChild("Log content");

    ImGui::TextUnformatted(LOG_STREAM.str().c_str());

    if (ImGui::GetScrollY() != ImGui::GetScrollMaxY() && !autoScrollChanged)
        m_autoScroll = false;

    if (m_autoScroll)
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();

    ImGui::End();

    return shouldContinue;
}

}  // namespace labeeri::Engine
