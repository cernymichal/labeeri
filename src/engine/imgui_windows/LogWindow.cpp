#include "LogWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "../Application.h"

namespace labeeri::engine {

LogWindow::LogWindow() {
}

void LogWindow::render() {
    ImGui::Begin("Log");

    bool autoScrollChanged = ImGui::Checkbox("Auto-scroll", &m_autoScroll);
    ImGui::SameLine(ImGui::GetWindowWidth() - 100);
    if (ImGui::SmallButton("Clear"))
        LAB_LOGSTREAM.str("");
    ImGui::SameLine();
    if (ImGui::SmallButton("Copy"))
        glfwSetClipboardString(LAB_APP.window(), LAB_LOGSTREAM.str().c_str());

    ImGui::Separator();

    ImGui::BeginChild("Log content");

    ImGui::TextUnformatted(LAB_LOGSTREAM.str().c_str());

    if (ImGui::GetScrollY() != ImGui::GetScrollMaxY() && !autoScrollChanged)
        m_autoScroll = false;

    if (m_autoScroll)
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();

    ImGui::End();
}

}  // namespace labeeri::engine
