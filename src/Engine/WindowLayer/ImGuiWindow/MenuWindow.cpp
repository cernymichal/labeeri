#include "MenuWindow.h"

#include <imgui.h>

#include "Engine/Application.h"
#include "Engine/Window/IWindow.h"
#include "Engine/WindowLayer/ImGuiWindow/LogWindow.h"

namespace labeeri::Engine {

static void postprocessingSection() {
    if (!ImGui::CollapsingHeader("Postprocessing"))
        return;

    if (!LAB_CURRENT_SCENE)
        return;

    auto& parameters = LAB_CURRENT_SCENE->m_renderParameters;

    ImGui::InputFloat("Exposure", &parameters.postprocessing.exposure);
    // ImGui::InputFloat("Contrast", &parameters.postprocessing.contrast);
    // ImGui::InputFloat("Brightness", &parameters.postprocessing.brightness);
    // ImGui::InputFloat("Saturation", &parameters.postprocessing.saturation);
    ImGui::InputFloat("Gamma", &parameters.postprocessing.gamma);
}

static void fogSection() {
    if (!ImGui::CollapsingHeader("Fog"))
        return;

    if (!LAB_CURRENT_SCENE)
        return;

    auto& parameters = LAB_CURRENT_SCENE->m_renderParameters;

    ImGui::ColorEdit3("Color", glm::value_ptr(parameters.fog.color));
    ImGui::SliderFloat("Density", &parameters.fog.density, 0, 1);
}

MenuWindow::MenuWindow() {
    m_VSync = LAB_WINDOW->VSync();
}

bool MenuWindow::draw() {
    ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);

    ImGui::Begin(m_name.c_str());

    if (ImGui::Button("Open Log"))
        LAB_IMGUI->addWindow(std::make_unique<LogWindow>());

    ImGui::Separator();

    postprocessingSection();
    fogSection();

    ImGui::Separator();

    bool vSyncChanged = ImGui::Checkbox("VSync", &m_VSync);
    if (vSyncChanged)
        LAB_WINDOW->setVSync(m_VSync);

    auto framerate = ImGui::GetIO().Framerate;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / framerate, framerate);
    ImGui::Text("%u entities", LAB_ECS ? LAB_ECS->m_entityManager->entityCount() : 0);

    ImGui::End();

    return true;
}

}  // namespace labeeri::Engine
