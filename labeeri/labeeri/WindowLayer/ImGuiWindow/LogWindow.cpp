#include "LogWindow.h"

#include "Utils/imgui.h"
#include "Window/IWindow.h"

namespace labeeri {

bool LogWindow::draw() {
    vec2 contentScale = LAB_WINDOW->contentScale();

    ImGui::SetNextWindowSize(vec2(800, 600) * contentScale, ImGuiCond_FirstUseEver);

    bool shouldContinue = true;
    ImGui::Begin(m_name.c_str(), &shouldContinue);

    bool autoScrollChanged = ImGui::Checkbox("Auto-scroll", &m_autoScroll);
    ImGui::SameLine(ImGui::GetWindowWidth() - 100 * contentScale.x);
    if (ImGui::SmallButton("Clear"))
        LAB_LOG_STREAM.str("");
    ImGui::SameLine();
    if (ImGui::SmallButton("Copy"))
        LAB_WINDOW->setClipboardContent(LAB_LOG_STREAM.str().c_str());

    ImGui::Separator();

    ImGui::BeginChild("Log content");

    ImGui::TextUnformatted(LAB_LOG_STREAM.str().c_str());

    if (ImGui::GetScrollY() != ImGui::GetScrollMaxY() && !autoScrollChanged)
        m_autoScroll = false;

    if (m_autoScroll)
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();

    ImGui::End();

    return shouldContinue;
}

}  // namespace labeeri
