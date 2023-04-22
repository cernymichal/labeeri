#include "MenuWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "../Application.h"

namespace labeeri::engine {

MenuWindow::MenuWindow() {
    glfwSwapInterval(m_VSync ? 1 : 0);
}

void MenuWindow::render() {
    ImGui::Begin("Menu");

    bool vSyncChanged = ImGui::Checkbox("VSync", &m_VSync);
    if (vSyncChanged)
        glfwSwapInterval(m_VSync ? 1 : 0);

    bool throwException = ImGui::Button("Exception");

    ImGui::Separator();

    auto framerate = ImGui::GetIO().Framerate;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / framerate, framerate);

    ImGui::End();

    if (throwException)
        throw std::runtime_error("Exception thrown from MenuWindow");
}

}  // namespace labeeri::engine
